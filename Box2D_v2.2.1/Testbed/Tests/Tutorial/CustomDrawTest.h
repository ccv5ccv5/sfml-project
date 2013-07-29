#ifndef __CUSTOM_DRAW_TEST_H__
#define __CUSTOM_DRAW_TEST_H__

#include <vector>
#include "Ball.h"

class CustomDrawTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  CustomDrawTest() {
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

    Ball *ball;
    for(int i = 0; i < 20; ++i){
      float radius = 1 + 2 * (rand()/(float)RAND_MAX);
      ball = new Ball(m_world, radius);
      balls.push_back(ball);
    }
  }

  void Step(Settings *settings){
    for(int i = 0; i < balls.size(); ++i)
      balls[i]->renderAtBodyPosition();
    Test::Step(settings);
  }

  static Test* Create(){
    return new CustomDrawTest;
  }
 private:
  std::vector<Ball*> balls;
};

#endif
