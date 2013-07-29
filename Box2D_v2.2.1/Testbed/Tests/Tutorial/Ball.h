#ifndef __BALL_H__
#define __BALL_H__

class Ball {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  Ball(b2World *world, float radius){
    m_body = NULL;
    m_radius = radius;

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    m_body = world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius;
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;

    m_body->CreateFixture(&myFixtureDef);
  }
  ~Ball() {}

  void render(){
    //Use velocity to change color
    b2Vec2 vel = m_body->GetLinearVelocity();
    float red = vel.Length() / 20.0f;
    red = min(1.0f, red);
    glColor3f(red, 0.5, 0.5);

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
};

#endif
