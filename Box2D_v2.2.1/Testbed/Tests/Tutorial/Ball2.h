#ifndef __BALL2_H__
#define __BALL2_H__

class Ball2 {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  float m_radius, m_angle;
  b2Vec2 m_position, m_linearVelocity;

 public:
  Ball2(b2World *world, float radius){
    m_radius = radius;

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    b2Body *body = world->CreateBody(&myBodyDef);
    
    //Can add any item (void*) into a b2Body, b2Fixture, or b2Joint
    body->SetUserData(this);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0);
    circleShape.m_radius = m_radius;
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.density = 1;

    body->CreateFixture(&myFixtureDef);
  }
  ~Ball2() {}

  void render(){
    //Use velocity to change color
    float red = m_linearVelocity.Length() / 20.0f;
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
    glPushMatrix();
    {
      glTranslatef(m_position.x, m_position.y, 0);
      glRotatef(m_angle * RADTODEG, 0, 0, 1);
      glScalef(m_radius, m_radius, 1); //x, y, z
      render();
    }
    glPopMatrix();
  }
};

#endif
