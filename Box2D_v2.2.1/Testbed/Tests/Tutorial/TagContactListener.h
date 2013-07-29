#ifndef __TAG_CONTACT_LISTENER_H__
#define __TAG_CONTACT_LISTENER_H__

#include "Ball3.h"

class TagContactListener : public b2ContactListener {
 public:
  void BeginContact(b2Contact *contact) {
    void *bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void *bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyUserDataA && bodyUserDataB){
      tag(static_cast<Ball3*>(bodyUserDataA), static_cast<Ball3*>(bodyUserDataB));
    }
  }
};

#endif
