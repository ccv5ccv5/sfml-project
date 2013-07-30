#ifndef __SENSOR_TUT_H__
#define __SENSOR_TUT_H__

#include <vector>
#include "Ball4.h"
#include "SensorContactListener.h"

class SensorTut : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

  enum _entityCategory {
    BOUNDARY = 0x0001,
    FRIENDLY_SHIP = 0x0002,
    ENEMY_SHIP = 0x0004,
    FRIENDLY_AIRCRAFT = 0x0008,
    ENEMY_AIRCRAFT = 0x0010,
    FRIENDLY_TOWER = 0x0020,
    RADAR_SENSOR = 0x0040,
  };

 public:
  SensorTut() {
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

    m_world->SetContactListener(&sensorListener);
    m_world->SetGravity( b2Vec2(0, 0) );

    b2Color red(1, 0, 0);
    b2Color green(0, 1, 0);

    Ball4 *ship = new Ball4(m_world, 3, green, FRIENDLY_SHIP, BOUNDARY | FRIENDLY_TOWER);
    
    //Sensors allow for contacts to occur while ignoring collisions with everything
    b2CircleShape circleShape;
    circleShape.m_radius = 8;
    myFixtureDef.shape = &circleShape;
    myFixtureDef.isSensor = true;
    myFixtureDef.filter.categoryBits = RADAR_SENSOR;
    myFixtureDef.filter.maskBits = ENEMY_AIRCRAFT;
    ship->m_body->CreateFixture(&myFixtureDef);

    balls.push_back(ship);

    for(int i = 0; i < 3; ++i){
      balls.push_back( new Ball4(m_world, 1, red, ENEMY_AIRCRAFT, 
				 BOUNDARY | RADAR_SENSOR) );
    }

    Ball4 *tower = new Ball4(m_world, 1, green, FRIENDLY_TOWER, FRIENDLY_SHIP);
    tower->m_body->SetType(b2_kinematicBody);

    float radius = 8;
    b2Vec2 vertices[8];

    vertices[0].Set(0, 0);
    for(int i = 0; i < 7; ++i){
      float angle = i / 6.0 * 90 * DEGTORAD;
      vertices[i+1].Set(radius * cosf(angle), radius * sinf(angle));
    }

    polyShape.Set(vertices, 8);
    myFixtureDef.shape = &polyShape;
    tower->m_body->CreateFixture(&myFixtureDef);

    tower->m_body->SetAngularVelocity(45 * DEGTORAD);

    balls.push_back(tower);
  }

  void Step(Settings *settings){
    for(int i = 0; i < balls.size(); ++i)
      balls[i]->renderAtBodyPosition();
    Test::Step(settings);
  }

  static Test* Create(){
    return new SensorTut;
  }
 private:
  std::vector<Ball4*> balls;
  SensorContactListener sensorListener;
};

#endif
