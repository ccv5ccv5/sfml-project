#ifndef __FOO_TEST_H__
#define __FOO_TEST_H__

class FooTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  FooTest() { 
    //Definition of a body (not an actual item per-se)
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    myBodyDef.angle = 0;

    dynamicBody = m_world->CreateBody(&myBodyDef);

    //Need to create a shape for the body and add a fixture
    //to it to get mass
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1, 1);

    b2FixtureDef boxFixtureDef;
    boxFixtureDef.shape = &boxShape;
    boxFixtureDef.density = 1; // Density * Area = Mass
    dynamicBody->CreateFixture(&boxFixtureDef);

    //Move over 10 right, 20 up, and 1 RADIAN counter-clockwise
    dynamicBody->SetTransform( b2Vec2(10, 20), 45 * DEGTORAD);

    //Move up and left while spinning right initially
    dynamicBody->SetLinearVelocity(b2Vec2(-5, 5));
    dynamicBody->SetAngularVelocity(-90 * DEGTORAD);

    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 10);

    //Velocity changes have no effect on static bodies
    b2Body *staticBody = m_world->CreateBody(&myBodyDef);
    staticBody->CreateFixture(&boxFixtureDef);

    myBodyDef.type = b2_kinematicBody;
    myBodyDef.position.Set(-18, 11);

    //Gravity and collisions do not affect kinematic bodies
    b2Body *kinematicBody = m_world->CreateBody(&myBodyDef);
    kinematicBody->CreateFixture(&boxFixtureDef);

    kinematicBody->SetLinearVelocity(b2Vec2(10, 0));
    kinematicBody->SetAngularVelocity(360 * DEGTORAD);
  }

  void Step(Settings *settings){
    Test::Step(settings);

    b2Vec2 pos = dynamicBody->GetPosition();
    float angle = dynamicBody->GetAngle();
    b2Vec2 linearVel = dynamicBody->GetLinearVelocity();
    float angularVel = dynamicBody->GetAngularVelocity();

    m_debugDraw.DrawString(5, m_textLine, 
			   "Position:%.3f,%.3f Angle:%.3f", pos.x, pos.y, 
			   angle * RADTODEG);
    m_textLine += 15;
    m_debugDraw.DrawString(5, m_textLine, 
			   "Linear Vel:%.3f,%.3f Angle Vel:%.3f", linearVel.x, linearVel.y,
			   angularVel * RADTODEG);
    m_textLine += 15;
  }

  static Test* Create(){
    return new FooTest;
  }
 private:
  b2Body *dynamicBody;
};

#endif
