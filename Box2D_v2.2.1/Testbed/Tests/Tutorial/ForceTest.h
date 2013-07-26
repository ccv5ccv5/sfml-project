#ifndef __FORCE_TEST_H__
#define __FORCE_TEST_H__

class ForceTest : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f

 public:
  ForceTest() {
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

    forceOn = false;
    torqueOn = false;
  }

  void Step(Settings *settings){
    Test::Step(settings);

    if(forceOn) {
      //Applies force, but in one time step, ignoring other forces
      bodies[0]->ApplyForce(b2Vec2(0, 50), bodies[0]->GetWorldCenter());
    }
    if(torqueOn) {
      bodies[0]->ApplyTorque(20);
    }
  }

  void Keyboard(unsigned char key){
    /*
     * GetWorldCenter() gets the center of mass for the BODY
     * GetWorldPoint(b2Vec2(x,y)) gets the point in the world corresponding to
     *    (x,y) in the body's coordinate plane
     * Forces applied on other parts of the BODY will be applied realistically
     *    causing spinning and the like
     */
    switch(key) {
    case 'q': 
      forceOn = !forceOn;
      break;
    case 'w':
      //Immediately applies force, ignoring others
      bodies[1]->ApplyLinearImpulse(b2Vec2(0, 50), bodies[1]->GetWorldCenter());
      break;
    case 'e':
      //Teleportation, essentially
      bodies[2]->SetTransform(b2Vec2(10, 20), 0);
      break;
    case 'a':
      torqueOn = !torqueOn;
      break;
    case 's':
      bodies[1]->ApplyAngularImpulse(20);
      break;
    default:
      Test::Keyboard(key);
    }

    
  }

  static Test* Create(){
    return new ForceTest;
  }
 private:
  b2Body *bodies[3];
  bool forceOn;
  bool torqueOn;
};

#endif
