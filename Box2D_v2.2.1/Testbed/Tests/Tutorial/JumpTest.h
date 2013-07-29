#ifndef __JUMP_TEST_H__
#define __JUMP_TEST_H__

class JumpTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  enum _moveState {
    MS_STOP, MS_LEFT, MS_RIGHT,
  };

  JumpTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(1, 1);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    myBodyDef.position.Set(10, 10);
    body = m_world->CreateBody(&myBodyDef);
    body->CreateFixture(&myFixtureDef);

    //To stop the body from rotating
    body->SetFixedRotation(true);

    //Box to encase dynamic body
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    b2Body *staticBody = m_world->CreateBody(&myBodyDef);

    polyShape.SetAsBox(20, 1, b2Vec2(0, 0), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(20, 1, b2Vec2(0, 40), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(1, 20, b2Vec2(-20, 20), 0);
    staticBody->CreateFixture(&myFixtureDef);
    polyShape.SetAsBox(1, 20, b2Vec2(20, 20), 0);
    staticBody->CreateFixture(&myFixtureDef);

    moveState = MS_STOP;
    remainingJumpSteps = 0;
  }

  void Step(Settings *settings){
    Test::Step(settings);

    // "Gradual" Acceleration with Linear Velocity
    /*
      b2Vec2 vel = body->GetLinearVelocity();

      switch(moveState){
      case MS_LEFT:  vel.x -= b2Max(vel.x - 0.1f, 5.0f); break;
      case MS_STOP:  vel.x *= 0.98; break;
      case MS_RIGHT: vel.x += b2Min(vel.x + 0.1f, 5.0f); break;
      }
      body->SetLinearVelocity(vel);
    */

    //Really gradual acceleration using forces
    b2Vec2 vel = body->GetLinearVelocity();
    float force = 0;
    switch(moveState){
    case MS_LEFT: if(vel.x > -5) force -= 50; break;
    case MS_STOP: force = vel.x * -10; break;
    case MS_RIGHT: if(vel.x < 5) force += 50; break;
    }
    body->ApplyForce(b2Vec2(force, 0), body->GetWorldCenter());

    if(remainingJumpSteps > 0){
      body->ApplyForce(b2Vec2(0, 500), body->GetWorldCenter());
      remainingJumpSteps--;
    }

    //NOTE: F = ma, but a = (v1 - v0)/t (change in velocity over time).
    //      Therefore F = m(v1 - v0)/t.
    //      If we want to apply force at each time step, t = 1/60, so
    //         force = body->GetMass() * velChange * (1/60.0f)
    //      An impulse applies a force in one time step, so we can do the below.

    //Gradual acceleration and movement using impulses
    /*
      b2Vec2 vel = body->GetLinearVelocity();
      float desiredVel = 0;
      switch(moveState){
      case MS_LEFT: desiredVel = -5; break;
      case MS_STOP: desiredVel = 0; break;
      case MS_RIGHT: desiredVel = 5; break;
      }
      
      float velChange = desiredVel - vel.x;
      float impulse = body->GetMass() * velChange;
      body->ApplyLinearImpulse(b2Vec2(impulse, 0), body->GetWorldCenter());
    */
  }

  void Keyboard(unsigned char key){

    switch(key){
    case 'a':
      moveState = MS_LEFT;
      break;
    case 's':
      moveState = MS_STOP;
      break;
    case 'd':
      moveState = MS_RIGHT;
      break;
      // Jump, ignoring all graviational force
    case 'j':
      {
	b2Vec2 linearVel = body->GetLinearVelocity();
	linearVel.y = 10;
	body->SetLinearVelocity(linearVel);
      }
      break;
      //Incremental jump, which has gravity applied to it
    case 'k':
      remainingJumpSteps = 6;
      break;
      //Quick jump BEFORE gravity acts, but has less effect as gravitational pull
      //gets stronger
    case 'l':
      {
	float impulse = body->GetMass() * 10;
	body->ApplyLinearImpulse(b2Vec2(0, impulse), body->GetWorldCenter());
      }
      break;
    default:
      Test::Keyboard(key);
    }
  }
    
  static Test* Create(){
    return new JumpTest;
  }
 private:
  b2Body *body;
  _moveState moveState;
  int remainingJumpSteps;
};

#endif
