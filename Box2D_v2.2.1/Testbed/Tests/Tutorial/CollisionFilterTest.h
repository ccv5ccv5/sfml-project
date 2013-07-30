#ifndef __COLLISION_FILTER_TEST_H__
#define __COLLISION_FILTER_TEST_H__

#include <vector>
#include "Ball4.h"

class CollisionFilterTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

  enum _entityCategory {
    BOUNDARY = 0x0001,
    FRIENDLY_SHIP = 0x0002,
    ENEMY_SHIP = 0x0004,
    FRIENDLY_AIRCRAFT = 0x0008,
    ENEMY_AIRCRAFT = 0x0010,
  };

 public:
  CollisionFilterTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(1, 1);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;
    myFixtureDef.restitution = 1;

    /*
     * Special group classifications for collision
     * RULES:
     *   1) If either fixture's groupIndex is 0, it will check the bits
     *   2) If both groupIndex are non-zero but different, it will check the bits
     *   3) If both groupIndex are same and positive, they ALWAYS collide
     *   4) If both groupIndex are same and negative, they NEVER collide
     */
    myFixtureDef.filter.groupIndex = -1;

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

    m_world->SetGravity( b2Vec2(0, 0) );

    b2Color red(1, 0, 0);
    b2Color green(0, 1, 0);

    for(int i = 0; i < 3; ++i){
      balls.push_back( new Ball4(m_world, 3, green, FRIENDLY_SHIP, 
				 BOUNDARY | FRIENDLY_SHIP | ENEMY_SHIP) );
    }
    for(int i = 0; i < 3; ++i){
      balls.push_back( new Ball4(m_world, 3, red, ENEMY_SHIP, 
				 BOUNDARY | FRIENDLY_SHIP | ENEMY_SHIP) );
    }
    for(int i = 0; i < 3; ++i){
      balls.push_back( new Ball4(m_world, 1, green, FRIENDLY_AIRCRAFT, 
				 BOUNDARY | ENEMY_AIRCRAFT) );
    }
    for(int i = 0; i < 3; ++i){
      balls.push_back( new Ball4(m_world, 1, red, ENEMY_AIRCRAFT, 
				 BOUNDARY | FRIENDLY_AIRCRAFT) );
    }
  }

  void Step(Settings *settings){
    for(int i = 0; i < balls.size(); ++i)
      balls[i]->renderAtBodyPosition();
    Test::Step(settings);
  }

  static Test* Create(){
    return new CollisionFilterTest;
  }
 private:
  std::vector<Ball4*> balls;
};

#endif
