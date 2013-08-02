#ifndef __DISEASE_CONTACT_LISTENER_H__
#define __DISEASE_CONTACT_LISTENER_H__

#include "Ball5.h"

class DiseaseContactListener : public b2ContactListener {
 public:
  void BeginContact(b2Contact *contact) {
    void *bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
    void *bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
    if(bodyUserDataA && bodyUserDataB){
      tag(static_cast<Ball5*>(bodyUserDataA), static_cast<Ball5*>(bodyUserDataB));
    }
  }
};

#endif
