#ifndef __JOINT_REVOLUTE_TEST_H__
#define __JOINT_REVOLUTE_TEST_H__

class JointRevoluteTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  enum _moveState {
    MS_STOP, MS_LEFT, MS_RIGHT,
  };

  JointRevoluteTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(2, 2);
    
    b2CircleShape circleShape;
    circleShape.m_radius = 2;

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    myBodyDef.position.Set(-3, 10);
    bodyA = m_world->CreateBody(&myBodyDef);
    bodyA->CreateFixture(&myFixtureDef);

    myBodyDef.position.Set(3, 10);
    myFixtureDef.shape = &circleShape;

    bodyB = m_world->CreateBody(&myBodyDef);
    bodyB->CreateFixture(&myFixtureDef);

    //Box to encase dynamic body
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    b2Body *staticBody = m_world->CreateBody(&myBodyDef);

    myFixtureDef.shape = &polyShape;

    polyShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);
    staticBody->CreateFixture(&myFixtureDef);

    moveState = MS_STOP;

    //Revolute joints fix two bodies some distance from each other
    //and allows rotation relative to each other.
    b2RevoluteJointDef revoluteJointDef;

    //These three are common amongst all joints
    revoluteJointDef.bodyA = bodyA; //First body to be connected
    revoluteJointDef.bodyB = bodyB; //Second body
    revoluteJointDef.collideConnected = false; //Should they collide against each other?

    //The following settings are unique to RevoluteJoint

    //Local Anchors are relative to the BODY, not the world, not the fixture
    revoluteJointDef.localAnchorA.Set(2, 2); //Where should the joint be placed on BodyA?
    revoluteJointDef.localAnchorB.Set(0, 0); //Ditto for BodyB.

    //We can set limits to how far the joint can rotate. It will try its best to
    //enforce the limit if enabled. You MUST set a lower and upper limit to use this.
    revoluteJointDef.enableLimit = true; //Is there a rotation limit?
    revoluteJointDef.lowerAngle = -45 * DEGTORAD; //What's the lowest angle joint can be at?
    revoluteJointDef.upperAngle = 45 * DEGTORAD;  //What's the highest?

    revoluteJointDef.enableMotor = true; //Shall we use a motor to provide constant force?
    revoluteJointDef.maxMotorTorque = 5; //Maximum torque?
    revoluteJointDef.motorSpeed = 90 * DEGTORAD; //How fast is the motor going?
    
    //When creating the joint, CreateJoint() returns a b2Joint*, superclass of all joints
    //so make sure to cast down to appropriate subclass
    joint = (b2RevoluteJoint *)m_world->CreateJoint(&revoluteJointDef);
  }

  void Step(Settings *settings){
    Test::Step(settings);

    m_debugDraw.DrawString(5, m_textLine, "Current joint angle: %f deg", 
			    joint->GetJointAngle() * RADTODEG);
    m_textLine += 15;
    m_debugDraw.DrawString(5, m_textLine, "Current joint speed: %f deg/s", 
			    joint->GetJointSpeed() * RADTODEG);
    m_textLine += 15;

    //Try to force the motor to go the other way [kinda doesn't work right]
    if(joint->GetJointAngle() <= joint->GetLowerLimit() || 
       joint->GetJointAngle() >= joint->GetUpperLimit())
      {
	joint->SetMotorSpeed(-joint->GetMotorSpeed());
      }
  }

  void Keyboard(unsigned char key){

    switch(key){
    case 'q': joint->SetMotorSpeed(-joint->GetMotorSpeed()); break;
    default:
      Test::Keyboard(key);
    }
  }
    
  static Test* Create(){
    return new JointRevoluteTest;
  }
 private:
  b2Body *bodyA, *bodyB;
  _moveState moveState;
  b2RevoluteJoint *joint;
};

#endif
