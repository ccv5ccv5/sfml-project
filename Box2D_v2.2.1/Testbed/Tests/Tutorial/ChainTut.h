#ifndef __CHAIN_TUT_H__
#define __CHAIN_TUT_H__

class ChainTut : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  enum _moveState {
    MS_STOP, MS_LEFT, MS_RIGHT,
  };

  ChainTut() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(2, 2);
    
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

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

    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(5, 10);
    polyShape.SetAsBox(1, 0.25);

    //We can use this joint to create a chain!
    b2RevoluteJointDef revoluteJointDef;
    b2Body *link = m_world->CreateBody(&myBodyDef);
    link->CreateFixture(&myFixtureDef);

    for(int i = 0; i < 10; ++i){
      b2Body *newLink = m_world->CreateBody(&myBodyDef);
      newLink->CreateFixture(&myFixtureDef);

      revoluteJointDef.bodyA = link;
      revoluteJointDef.bodyB = newLink;
      revoluteJointDef.collideConnected = false;
      revoluteJointDef.localAnchorA.Set(0.75, 0); 
      revoluteJointDef.localAnchorB.Set(-0.75, 0); 
      
      m_world->CreateJoint(&revoluteJointDef);
      link = newLink;
    }

    b2CircleShape circleShape;
    circleShape.m_radius = 2;
    myFixtureDef.shape = &circleShape;

    b2Body *chainBase = m_world->CreateBody(&myBodyDef);
    chainBase->CreateFixture(&myFixtureDef);

    //Using the ever-present static body(m_groundBody), we can anchor
    //part of the chain down
    revoluteJointDef.bodyA = m_groundBody;
    revoluteJointDef.bodyB = chainBase;
    revoluteJointDef.localAnchorA.Set(4, 20);
    revoluteJointDef.localAnchorB.Set(0, 0);
    
    m_world->CreateJoint(&revoluteJointDef);

    revoluteJointDef.bodyA = link;
    revoluteJointDef.bodyB = chainBase;
    revoluteJointDef.localAnchorA.Set(0.75, 0);
    revoluteJointDef.localAnchorB.Set(1.75, 0);

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
  }

  void Keyboard(unsigned char key){

    switch(key){
    default:
      Test::Keyboard(key);
    }
  }
    
  static Test* Create(){
    return new ChainTut;
  }
 private:
  b2Body *bodyA, *bodyB;
  _moveState moveState;
  b2RevoluteJoint *joint;
};

#endif
