#ifndef __BALL5_H__
#define __BALL5_H__

#include <vector>

class Ball5 {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  bool isIt;

 public:
  Ball5(b2World *world, float radius){
    m_body = NULL;
    m_radius = radius;

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    m_body = world->CreateBody(&myBodyDef);
    m_body->SetUserData(this);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius;
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;

    m_body->CreateFixture(&myFixtureDef);

    m_numContacts = 0;
    isIt = false;
  }
  ~Ball5() {
    m_body->GetWorld()->DestroyBody(m_body);
  }

  void startContact() { m_numContacts++; }
  void endContact() { m_numContacts--; }


  void render(){
    //if(m_numContacts > 0)
    if(isIt)
      glColor3f(1, 0, 0);
    else
      glColor3f(1, 1, 1);

    glPointSize(4);
    glBegin(GL_POINTS);
    {
      glVertex2f(0, 0);
      glVertex2f(-0.5, 0.5);
      glVertex2f(0.5, 0.5);
    }
    glEnd();

    glBegin(GL_LINES);
    {
      glVertex2f(-0.5, -0.5);
      glVertex2f(-0.16, -0.6);
      glVertex2f(0.16, -0.6);
      glVertex2f(0.5, -0.5);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    {
      for(float a = 0; a < 360 * DEGTORAD; a += 30 * DEGTORAD){
	glVertex2f(sinf(a), cosf(a));
      }
    }
    glEnd();
  }

  void renderAtBodyPosition(){
    b2Vec2 pos = m_body->GetPosition();
    float angle = m_body->GetAngle();

    glPushMatrix();
    {
      glTranslatef(pos.x, pos.y, 0);
      glRotatef(angle * RADTODEG, 0, 0, 1);
      glScalef(m_radius, m_radius, 1); //x, y, z
      render();
    }
    glPopMatrix();
  }
 private:
  b2Body *m_body;
  float m_radius;
  int m_numContacts;

};

std::vector<Ball5*> ballScheduledForRemoval;
bool outbreak = false;
void tag(Ball5 *b1, Ball5 *b2){
  if(!outbreak)
    return;
  if(b1->isIt){
    ballScheduledForRemoval.push_back(b1);
    b2->isIt = true;
  } else if(b2->isIt){
    ballScheduledForRemoval.push_back(b2);
    b1->isIt = true;
  }
}

#endif
