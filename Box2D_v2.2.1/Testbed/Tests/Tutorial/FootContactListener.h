#ifndef __FOOT_CONTACT_LISTENER_H__
#define __FOOT_CONTACT_LISTENER_H__

int numFootContacts;

class FootContactListener : public b2ContactListener {
  void BeginContact(b2Contact *contact){
    void *fixtureUserData = contact->GetFixtureA()->GetUserData();
    if( fixtureUserData == (void *)3)
      numFootContacts++;

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if( fixtureUserData == (void *)3)
      numFootContacts++;
  }

  void EndContact(b2Contact *contact){
    void *fixtureUserData = contact->GetFixtureA()->GetUserData();
    if( fixtureUserData == (void *)3)
      numFootContacts--;

    fixtureUserData = contact->GetFixtureB()->GetUserData();
    if( fixtureUserData == (void *)3)
      numFootContacts--;
  }
};

#endif
