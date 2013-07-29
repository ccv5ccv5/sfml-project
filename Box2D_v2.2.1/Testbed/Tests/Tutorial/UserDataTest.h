#ifndef __USER_DATA_TEST_H__
#define __USER_DATA_TEST_H__

#include <vector>
#include "Ball2.h"

class UserDataTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  UserDataTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(1, 1);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

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

    Ball2 *ball;
    for(int i = 0; i < 20; ++i){
      float radius = 1 + 2 * (rand()/(float)RAND_MAX);
      ball = new Ball2(m_world, radius);
    }
  }

  void Step(Settings *settings){
    Ball2 *ball;
    //Not recommended for rendering
    for(b2Body *b = m_world->GetBodyList(); b; b = b->GetNext()){
      ball = static_cast<Ball2 *>( b->GetUserData() );
      if(ball != NULL){
	ball->m_position = b->GetPosition();
	ball->m_angle = b->GetAngle();
	ball->m_linearVelocity = b->GetLinearVelocity();
	ball->renderAtBodyPosition();
      }
    }
    Test::Step(settings);
  }

  static Test* Create(){
    return new UserDataTest;
  }
 private:
  std::vector<Ball2*> balls;
};

#endif
