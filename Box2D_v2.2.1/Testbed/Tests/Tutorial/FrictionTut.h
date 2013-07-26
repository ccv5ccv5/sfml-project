#ifndef __FRICTION_TUT_H__
#define __FRICTION_TUT_H__

class FrictionTut : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  FrictionTut() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;
    myBodyDef.position.Set(0, 20);

    //Changing the gravity of the world
    m_world->SetGravity(b2Vec2(0, 0));

    b2Body *d1 = m_world->CreateBody(&myBodyDef);

    b2PolygonShape polyShape;

    //Fixture properties can be changed at runtime with Set methods
    //but require a pointer to the fixture
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    for(int i = 0; i < 4; ++i){
      b2Vec2 pos(sinf(i * 90 * DEGTORAD), cosf(i * 90 * DEGTORAD));
      polyShape.SetAsBox(1, 1, pos, 0);

      //When fixtures collide, resulting friction value tends toward the lowest of them
      myFixtureDef.friction = i/4.0; //property of the fixture with range [0, 1]

      //Restitution affects how 'bouncy' fixture is, with range [0, 1]
      //When fixtures collide, resulting restitution value tends towards the highest
      myFixtureDef.restitution = i/4.0;
      d1->CreateFixture(&myFixtureDef);

    }
    myFixtureDef.friction = 1;
    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);

    //Replaces the SetAsEdge method of b2PolygonShape
    b2EdgeShape edgeShape;
    edgeShape.Set(b2Vec2(-15, 0), b2Vec2(15, 3));
    myFixtureDef.shape = &edgeShape;

    b2Body *staticBody = m_world->CreateBody(&myBodyDef);
    staticBody->CreateFixture(&myFixtureDef);

    /*
     * Can grab linked list of fixtures of a body with
     *   b2Fixture *f = d1->GetFixtureList();
     * Can go to the next with 
     *   f->GetNext();
     * If pointer is NULL, list is done.
     */
  }
  void Step(Settings *settings){
    Test::Step(settings);
  }
  static Test* Create(){
    return new FrictionTut;
  }
 private:

};

#endif
