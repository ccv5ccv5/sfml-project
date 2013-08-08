#ifndef __JOINT_PRISMATIC_TEST_H__
#define __JOINT_PRISMATIC_TEST_H__

class JointPrismaticTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  enum _moveState {
    MS_STOP, MS_LEFT, MS_RIGHT,
  };

  JointPrismaticTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(5, 3);
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    myBodyDef.position.Set(-10, 10);
    bodyA = m_world->CreateBody(&myBodyDef);
    bodyA->CreateFixture(&myFixtureDef);
    bodyA->SetFixedRotation(true);

    myBodyDef.position.Set(-4, 10);
    polyShape.SetAsBox(1, 4);

    bodyB = m_world->CreateBody(&myBodyDef);
    bodyB->CreateFixture(&myFixtureDef);

    myBodyDef.position.Set(0, 10);
    bodyC = m_world->CreateBody(&myBodyDef);

    polyShape.SetAsBox(0.25, 3.5);
    bodyC->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(3.5, 0.25, b2Vec2(3.5, -3.5), 0);
    bodyC->CreateFixture(&myFixtureDef);

    myBodyDef.position.Set(10, 10);
    myFixtureDef.density = 0.2;
    polyShape.SetAsBox(3, 3);
    m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

    //Box to encase dynamic body
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    b2Body *staticBody = m_world->CreateBody(&myBodyDef);

    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    polyShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);
    staticBody->CreateFixture(&myFixtureDef);

    moveState = MS_STOP;

    //Prismatic Joints allow translation in a particular direction relative
    //to body A
    b2PrismaticJointDef prismaticJointDef;
    prismaticJointDef.bodyA = bodyA;
    prismaticJointDef.bodyB = bodyB;
    
    //The following settings are unique to PrismaticJoint

    //Local Axis is the DIRECTION relative to BodyA that BodyB can move
    //Make sure to normalize it to ensure it is a direction
    prismaticJointDef.localAxisA.Set(0, 1);
    prismaticJointDef.localAxisA.Normalize();

    //Just like Revolute Joint. Where on the body should joint attach?
    prismaticJointDef.localAnchorA.Set(6, -3);
    prismaticJointDef.localAnchorB.Set(-1, -4);

    //How much should BodyB be rotated counter-clockwise relative to BodyA's rotation?
    prismaticJointDef.referenceAngle = 5 * DEGTORAD;

    //Place a limit to how far and close bodyB can be moved.
    //You MUST set a lower and upper limit to use it.
    prismaticJointDef.enableLimit = true;
    prismaticJointDef.lowerTranslation = 0;
    prismaticJointDef.upperTranslation = 10;

    //A motor just like the Revolute Joint
    prismaticJointDef.enableMotor = true;
    prismaticJointDef.maxMotorForce = 500;
    prismaticJointDef.motorSpeed = -5;

    //Again, cast it from b2Joint* to b2PrismaticJoint*
    joint = (b2PrismaticJoint *)m_world->CreateJoint(&prismaticJointDef);

    //From here, attempting to complete the forklift
    prismaticJointDef.bodyA = bodyB;
    prismaticJointDef.bodyB = bodyC;

    prismaticJointDef.localAxisA.Set(1, 0);
    prismaticJointDef.localAxisA.Normalize();

    prismaticJointDef.localAnchorA.Set(1, -4);
    prismaticJointDef.localAnchorB.Set(-1, -3.5);
    
    prismaticJointDef.referenceAngle = 0;

    prismaticJointDef.enableMotor = true;

    jointB = (b2PrismaticJoint *)m_world->CreateJoint(&prismaticJointDef);
  }

  void Step(Settings *settings){
    Test::Step(settings);

    m_debugDraw.DrawString(5, m_textLine, "Current joint translation: %f", 
			    joint->GetJointTranslation() * RADTODEG);
    m_textLine += 15;
    m_debugDraw.DrawString(5, m_textLine, "Current joint speed: %f", 
			    joint->GetJointSpeed() * RADTODEG);
    m_textLine += 15;
  }

  void Keyboard(unsigned char key){
    switch(key){
    case 'q': joint->SetMotorSpeed(-5); break;
    case 'w': joint->SetMotorSpeed(0); break;
    case 'e': joint->SetMotorSpeed(5); break;
    case 'a': jointB->SetMotorSpeed(-5); break;
    case 's': jointB->SetMotorSpeed(0); break;
    case 'd': jointB->SetMotorSpeed(5); break;
    default:
      Test::Keyboard(key);
    }
  }
    
  static Test* Create(){
    return new JointPrismaticTest;
  }
 private:
  b2Body *bodyA, *bodyB, *bodyC;
  _moveState moveState;
  b2PrismaticJoint *joint, *jointB;
};

#endif
