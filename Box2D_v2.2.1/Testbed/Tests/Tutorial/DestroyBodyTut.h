#ifndef __DESTROY_BODY_TUT_H__
#define __DESTROY_BODY_TUT_H__

#include <iostream>
#include <vector>
#include "Ball5.h"
#include "MyContactListener.h"
#include "DiseaseContactListener.h"

class DestroyBodyTut : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  DestroyBodyTut() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(1, 1);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;
    myFixtureDef.restitution = 1;

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

    m_world->SetContactListener(&tagListener);
    m_world->SetGravity( b2Vec2(0, 0) );
    Ball5 *ball;
    for(int i = 0; i < 20; ++i){
      float radius = 1 + 2 * (rand()/(float)RAND_MAX);
      ball = new Ball5(m_world, radius);
      balls.push_back(ball);
    }
    balls[0]->isIt = true;
  }

  void Keyboard(unsigned char key){
    switch(key){
    case 'q': outbreak = true; break;
    default: Test::Keyboard(key);
    }
  }

  void Step(Settings *settings){
    Test::Step(settings);

    std::vector<Ball5*>::iterator it = ballScheduledForRemoval.begin();
    std::vector<Ball5*>::iterator end = ballScheduledForRemoval.end();

    //Any bodies, fixtures must be created AND destroyed OUTSIDE of the Step() loop
    //This is to prevent undefined behavior when the world is stepping through bodies

    //The practice used here is to keep a list of bodies to remove and when the Step()
    //is over, delete them.
    for(; it != end; ++it){
      Ball5 *dyingBall = *it;

      delete dyingBall;

      std::vector<Ball5*>::iterator it = std::find(balls.begin(), balls.end(), dyingBall);
      if(it != balls.end())
	balls.erase(it);
    }
    std::cerr << balls.size() << std::endl;
    ballScheduledForRemoval.clear();

    for(int i = 0; i < balls.size(); ++i)
      balls[i]->renderAtBodyPosition();
  }

  static Test* Create(){
    return new DestroyBodyTut;
  }
 private:
  std::vector<Ball5*> balls;
  MyContactListener contactListener;
  DiseaseContactListener tagListener;
};

#endif
