#ifndef __BALL4_H__
#define __BALL4_H__

#include <vector>

bool addedGroupIndex = false;

class Ball4 {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  b2Color m_color;
  b2Body *m_body;
  std::vector<Ball4*> visibleEnemies;
 public:
  Ball4(b2World *world, float radius, b2Color color, uint16 categoryBits, uint16 maskBits){
    m_body = NULL;
    m_radius = radius;
    m_color = color;
    
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
    
    //Category bits define what this fixture is
    myFixtureDef.filter.categoryBits = categoryBits;

    //Mask bits define what they can collide with
    myFixtureDef.filter.maskBits = maskBits;

    //if(!addedGroupIndex)
    //  myFixtureDef.filter.groupIndex = -1;
    //addedGroupIndex = true;
    m_body->CreateFixture(&myFixtureDef);
  }
  ~Ball4() {}

  void radarAcquireEnemy(Ball4 *enemy){
    visibleEnemies.push_back(enemy);
  }
  void radarLostEnemy(Ball4 *enemy){
    visibleEnemies.erase( std::find(visibleEnemies.begin(), visibleEnemies.end(), enemy) );
  }

  void render(){
    //Use velocity to change color
    if(visibleEnemies.size() > 0)
      glColor3f(1, 1, 0);
    else
      glColor3f(m_color.r, m_color.g, m_color.b);

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

    //Draw lines from sensor to enemies
    glColor3f(1, 1, 1);
    glLineStipple(1, 0xF0F0); //evenly dashed line
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    {
      for(int i = 0; i < visibleEnemies.size(); ++i){
	b2Vec2 enemyPos = visibleEnemies[i]->m_body->GetPosition();
	glVertex2f(pos.x, pos.y);
	glVertex2f(enemyPos.x, enemyPos.y);
      }
    }
    glEnd();
    glDisable(GL_LINE_STIPPLE);
  }
 private:

  float m_radius;
};

#endif
