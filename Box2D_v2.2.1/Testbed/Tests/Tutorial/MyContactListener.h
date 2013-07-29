#ifndef __MY_CONTACT_LISTENER_H__
#define __MY_CONTACT_LISTENER_H__

#include "Ball3.h"

class MyContactListener : public b2ContactListener {
 public:
  void BeginContact(b2Contact *contact) {
    void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if(bodyUserData){
      static_cast<Ball3*>(bodyUserData)->startContact();
    }

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyUserData){
      static_cast<Ball3*>(bodyUserData)->startContact();
    }
  }
  void EndContact(b2Contact *contact) {
    void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if(bodyUserData){
      static_cast<Ball3*>(bodyUserData)->endContact();
    }

    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyUserData){
      static_cast<Ball3*>(bodyUserData)->endContact();
    }
  }
};

#endif
