#ifndef __RAY_CAST_TUT_H__
#define __RAY_CAST_TUT_H__

class RayCastTut : public Test {
  #define DEGTORAD 0.0174532925f
  #define RADTODEG 57.2957795f
 public:
  float currentAngle;

 public:
  RayCastTut(){
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

    currentAngle = 0;
  }

  void recursiveRayCast(b2Vec2 p1, b2Vec2 p2){
    b2RayCastInput input;
    input.p1 = p1;
    input.p2 = p2;
    input.maxFraction = 1;
    
    float closestFraction = 1;
    b2Vec2 intersectionNormal(0, 0);
    for(b2Body *b = m_world->GetBodyList(); b; b = b->GetNext()){
      for(b2Fixture *f = b->GetFixtureList(); f; f = f->GetNext()){
	b2RayCastOutput output;

	//It seems it needs an int (for childIndex?), so I gave it a 0
	//Need to find out more about this call
	if( !f->RayCast (&output, input, 0) )
	  continue;
	if(output.fraction < closestFraction){
	  closestFraction = output.fraction;
	  intersectionNormal = output.normal;
	}
      }
    }

    b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    {
      glVertex2f(p1.x, p1.y);
      glVertex2f(intersectionPoint.x, intersectionPoint.y);
    }
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    {
      glVertex2f(intersectionPoint.x, intersectionPoint.y);
    }
    glEnd();

    b2Vec2 normalEnd = intersectionPoint + intersectionNormal;
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    {
      glVertex2f(intersectionPoint.x, intersectionPoint.y);
      glVertex2f(normalEnd.x, normalEnd.y);
    }
    glEnd();

    if(closestFraction == 1 || closestFraction == 0) return;

    b2Vec2 remainingRay = (p2 - intersectionPoint);
    b2Vec2 projectedOntoNormal = b2Dot(remainingRay, intersectionNormal) * intersectionNormal;
    b2Vec2 nextp2 = p2 - 2 * projectedOntoNormal;

    recursiveRayCast(intersectionPoint, nextp2);
  }

  void Step(Settings *settings){
    currentAngle += 360 / 2.0 / 60.0 * DEGTORAD;

    float rayLength = 25;
    b2Vec2 p1(0, 20);
    b2Vec2 p2 = p1 + rayLength * b2Vec2( sinf(currentAngle), cosf(currentAngle) );
    recursiveRayCast(p1, p2);

    /*
    b2RayCastInput input;
    input.p1 = p1;
    input.p2 = p2;
    input.maxFraction = 1;
    
    float closestFraction = 1;
    b2Vec2 intersectionNormal(0, 0);
    for(b2Body *b = m_world->GetBodyList(); b; b = b->GetNext()){
      for(b2Fixture *f = b->GetFixtureList(); f; f = f->GetNext()){
	b2RayCastOutput output;
	if( !f->RayCast (&output, input, 0) )
	  continue;
	if(output.fraction < closestFraction){
	  closestFraction = output.fraction;
	  intersectionNormal = output.normal;
	}
      }
    }

    b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    {
      glVertex2f(p1.x, p1.y);
      glVertex2f(intersectionPoint.x, intersectionPoint.y);
    }
    glEnd();

    glPointSize(5);
    glBegin(GL_POINTS);
    {
      glVertex2f(intersectionPoint.x, intersectionPoint.y);
    }
    glEnd();

    b2Vec2 normalEnd = intersectionPoint + intersectionNormal;
    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
    {
      glVertex2f(intersectionPoint.x, intersectionPoint.y);
      glVertex2f(normalEnd.x, normalEnd.y);
    }
    glEnd();
    */
    Test::Step(settings);
  }

  static Test* Create(){
    return new RayCastTut;
  }
};

#endif
