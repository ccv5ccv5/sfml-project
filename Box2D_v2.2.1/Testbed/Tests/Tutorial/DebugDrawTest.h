#ifndef __DEBUG_DRAW_TEST_H__
#define __DEBUG_DRAW_TEST_H__

#include "FooDraw.h"

class DebugDrawTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  DebugDrawTest() {
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

    m_world->SetDebugDraw(&myFooDraw);
  }

  void Step(Settings *settings){

    myFooDraw.SetFlags(DebugDraw::e_shapeBit);

    m_world->DrawDebugData();
    Test::Step(settings);
  }

  static Test* Create(){
    return new DebugDrawTest;
  }
 private:
  b2Body *body;
  FooDraw myFooDraw;
};

#endif
