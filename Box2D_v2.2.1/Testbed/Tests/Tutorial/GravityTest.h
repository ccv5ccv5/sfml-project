#ifndef __GRAVITY_TEST_H__
#define __GRAVITY_TEST_H__

class GravityTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  GravityTest() {
    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody;

    b2PolygonShape polyShape;
    polyShape.SetAsBox(1, 1);

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polyShape;
    myFixtureDef.density = 1;

    for(int i = 0; i < 3; ++i){
      myBodyDef.position.Set(-10 + i * 10, 20);
      bodies[i] = m_world->CreateBody(&myBodyDef);
      bodies[i]->CreateFixture(&myFixtureDef);
    }

    myBodyDef.type = b2_staticBody;
    myBodyDef.position.Set(0, 0);

    b2EdgeShape edge;
    edge.Set(b2Vec2(-15, 0), b2Vec2(15, 0));
    myFixtureDef.shape = &edge;

    m_world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);

    bodies[1]->SetGravityScale(0); //Scaling gravity in Box2D v2.2.1

    /*
      // Scaling gravity in Box2D v2.1.2
      //NOTE: Must be done EVERY time step as well
      bodies[1]->ApplyForce( bodies[1]->GetMass() * -m_world->GetGravity(), 
      bodies[1]->GetWorldCenter());
    */
  }

  void Step(Settings *settings){
    Test::Step(settings);

    /*
      bodies[1]->ApplyForce( bodies[1]->GetMass() * -m_world->GetGravity(), 
      bodies[1]->GetWorldCenter());
    */
  }

  void Keyboard(unsigned char key){
    Test::Keyboard(key);
  }

  static Test* Create(){
    return new GravityTest;
  }
 private:
  b2Body *bodies[3];
};

#endif
