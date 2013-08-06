#ifndef __CERTAIN_FOOT_CONTACT_LISTENER_H__
#define __CERTAIN_FOOT_CONTACT_LISTENER_H__

#include <set>

set<b2Fixture *> fixturesUnderfoot;

class CertainFootContactListener : public b2ContactListener {
  void BeginContact(b2Contact *contact){
    void *fixtureUserData = contact->GetFixtureA()->GetUserData();
    if( fixtureUserData == (void *)3)
      fixturesUnderfoot.insert(contact->GetFixtureB());

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if( fixtureUserData == (void *)3)
      fixturesUnderfoot.insert(contact->GetFixtureA());
  }

  void EndContact(b2Contact *contact){
    void *fixtureUserData = contact->GetFixtureA()->GetUserData();
    if( fixtureUserData == (void *)3)
      fixturesUnderfoot.erase(contact->GetFixtureB());

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if( fixtureUserData == (void *)3)
      fixturesUnderfoot.erase(contact->GetFixtureA());
  }
};

#endif
