#ifndef __ROTATE_TEST_H__
#define __ROTATE_TEST_H__

class RotateTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  RotateTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    b2Vec2 vertices[6];

    for(int i = 0; i < 6; ++i){
      float angle = -i/6.0 * 360 * DEGTORAD;
      vertices[i].Set(sinf(angle), cosf(angle));
    }
    vertices[0].Set(0, 4);
    polyShape.Set(vertices, 6);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    myBodyDef.position.Set(0, 10);
    body = m_world->CreateBody(&myBodyDef);
    body->CreateFixture(&myFixtureDef);

    m_world->SetGravity(b2Vec2(0, 0));

    clickedPoint = b2Vec2(0, 20);
  }

  void Step(Settings *settings){
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex2f(clickedPoint.x, clickedPoint.y);
    glEnd();

    //Calculate angle to move to so that body points at mouse click
    float bodyAngle = body->GetAngle();
    b2Vec2 toTarget = clickedPoint - body->GetPosition();
    float desiredAngle = atan2f(-toTarget.x, toTarget.y);

    m_debugDraw.DrawString(5, m_textLine, "Body Angle: %.3f", bodyAngle * RADTODEG);
    m_textLine += 15;
    m_debugDraw.DrawString(5, m_textLine, "Target Angle: %.3f", desiredAngle * RADTODEG);
    m_textLine += 15;
    

    //Make the rotation more gradual
    float totalRotation = desiredAngle - bodyAngle;
    while(totalRotation < -180 * DEGTORAD) totalRotation += 360 * DEGTORAD;
    while(totalRotation > 180 * DEGTORAD) totalRotation -= 360 * DEGTORAD;

    float change = 1 * DEGTORAD;
    float newAngle = bodyAngle + min(change, max(-change, totalRotation));

    body->SetTransform(body->GetPosition(), newAngle);

    Test::Step(settings);
  }

  void Keyboard(unsigned char key){
    Test::Keyboard(key);
  }

  void MouseDown(const b2Vec2& p){
    clickedPoint = p;

    Test::MouseDown(p);
  }
    
  static Test* Create(){
    return new RotateTest;
  }
 private:
  b2Body *body;
  b2Vec2 clickedPoint;
};

#endif
