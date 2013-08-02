#ifndef __AABB_TUT_H__
#define __AABB_TUT_H__

#include "MyQueryCallback.h"

// AABB stands for "Axis-Aligned Bounding Box"
// NOTE: The bounding box does not necessarily exactly cover any fixture
//       so some items will be selected even though the fixture itself does
//       not actually enter the selection box.
class AABBTut : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  b2Vec2 mouseDownPos, mouseUpPos;
 public:
  AABBTut(){
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);
    b2Body *staticBody = m_world->CreateBody(&myBodyDef);

    b2FixtureDef myFixtureDef;

    //Box made of edges
    b2Vec2 bl(-20, 0);
    b2Vec2 br(20, 0);
    b2Vec2 tl(-20, 40);
    b2Vec2 tr(20, 40);

    b2EdgeShape edgeShape;
    myFixtureDef.shape = &edgeShape;    

    edgeShape.Set(bl, br);
    staticBody->CreateFixture(&myFixtureDef);

    edgeShape.Set(tl, tr);
    staticBody->CreateFixture(&myFixtureDef);

    edgeShape.Set(bl, tl);
    staticBody->CreateFixture(&myFixtureDef);

    edgeShape.Set(br, tr);
    staticBody->CreateFixture(&myFixtureDef);

    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);
    
    b2PolygonShape polyShape;
    polyShape.SetAsBox(2, 2);

    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    for(int i = 0; i < 5; ++i){
      m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
    }

    b2CircleShape circleShape;
    circleShape.m_radius = 2;
    myFixtureDef.shape = &circleShape;
    for(int i = 0; i < 5; ++i){
      m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
    }
    
    m_world->SetGravity(b2Vec2(0, 0));
  }

  //Called when mouse button held down
  void MouseDown(const b2Vec2 &p){ 
    mouseDownPos = mouseUpPos = p; //Reset the box
    Test::MouseDown(p);
  }

  //Called when mouse button released
  void MouseUp(const b2Vec2 &p){
    mouseUpPos = p;
    Test::MouseUp(p);
  }

  void Step(Settings *settings){
    Test::Step(settings);

    b2Vec2 lower( min(mouseDownPos.x, mouseUpPos.x), min(mouseDownPos.y, mouseUpPos.y) );
    b2Vec2 upper( max(mouseDownPos.x, mouseUpPos.x), max(mouseDownPos.y, mouseUpPos.y) );

    //Draw the selection box
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    {
      glVertex2f(lower.x, lower.y);
      glVertex2f(upper.x, lower.y);
      glVertex2f(upper.x, upper.y);
      glVertex2f(lower.x, upper.y);
    }
    glEnd();

    MyQueryCallback query;

    //Selection box as AABB
    b2AABB aabb;
    aabb.lowerBound = lower;
    aabb.upperBound = upper;

    //Ask the world about what is inside the AABB
    //NOTE: There is also one for ray casting called
    //         void RayCast(b2RayCastCallback *, const b2Vec2 &p1, const b2Vec2 &p2);
    //      where the callback has one virtual function
    //         float32 ReportFixture(b2Fixture *, const b2Vec2 & intersectionPoint,
    //                               const b2Vec2 &intersectionNormal, float32 fraction);
    m_world->QueryAABB(&query, aabb);

    //Draw points at the center of each selected fixture
    glPointSize(6);
    glBegin(GL_POINTS);
    {
      for(int i = 0; i < query.foundBodies.size(); ++i){
	b2Vec2 pos = query.foundBodies[i]->GetPosition();
	glVertex2f( pos.x, pos.y );
      }
    }
    glEnd();
  }

  static Test* Create(){
    return new AABBTut;
  }
};

#endif
