#ifndef __FIXTURE_TUT_H__
#define __FIXTURE_TUT_H__

class FixtureTut : public Test {
 public:
  FixtureTut() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(-10, 20);

    b2Body *d1 = m_world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0,0); //position relative to body position
    circleShape.m_radius = 1;

    //Same body can have multiple fixtures, but each fixture will NOT act
    //independently
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape;

    //Will not be affected by gravity without density
    //due to not having mass
    myFixtureDef.density = 1; 

    d1->CreateFixture(&myFixtureDef);

    // Default limit of 8 vertices.
    // Must be placed in counter-clockwise order.
    // Polygone must be convex.
    b2Vec2 vertices[5];
    vertices[0].Set(-1 + 10, 2);
    vertices[1].Set(-1 + 10, 0);
    vertices[2].Set(0 + 10, -3);
    vertices[3].Set(1 + 10, 0);
    vertices[4].Set(1 + 10, 1);

    b2PolygonShape polyShape;
    polyShape.Set(vertices, 5); //Allows for up to 8 vertices

    myFixtureDef.shape = &polyShape;
    myBodyDef.position.Set(0, 20);

    b2Body *d2 = m_world->CreateBody(&myBodyDef);
    d1->CreateFixture(&myFixtureDef);

    polyShape.SetAsBox(2, 1, b2Vec2(20, 0), 0); //(half-width, half-height)
    myBodyDef.position.Set(10, 20);
    
    b2Body *d3 = m_world->CreateBody(&myBodyDef);
    d1->CreateFixture(&myFixtureDef);

    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);

    //Replaces the SetAsEdge method of b2PolygonShape
    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
    myFixtureDef.shape = &edgeShape;

    b2Body *staticBody = m_world->CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef);


  }
  void Step(Settings *settings){
    Test::Step(settings);
  }
  static Test* Create(){
    return new FixtureTut;
  }
 private:

};

#endif
