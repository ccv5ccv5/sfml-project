#ifndef __SENSOR_CONTACT_LISTENER_H__
#define __SENSOR_CONTACT_LISTENER_H__

#include "Ball4.h"

class SensorContactListener : public b2ContactListener {
 public:
  void BeginContact(b2Contact *contact) {
    Ball4 *radarEntity, *aircraftEntity;
    if(getRadarAndAircraft(contact, radarEntity, aircraftEntity)){
      radarEntity->radarAcquireEnemy(aircraftEntity);
    }
  }

  void EndContact(b2Contact *contact) {
    Ball4 *radarEntity, *aircraftEntity;
    if(getRadarAndAircraft(contact, radarEntity, aircraftEntity)){
      radarEntity->radarLostEnemy(aircraftEntity);
    }
  }

  bool getRadarAndAircraft(b2Contact *contact, Ball4*& radarEntity, Ball4*& aircraftEntity){
    b2Fixture *fixtureA = contact->GetFixtureA();
    b2Fixture *fixtureB = contact->GetFixtureB();

    bool isSensorA = fixtureA->IsSensor();
    bool isSensorB = fixtureB->IsSensor();

    //Ensure exactly one is a sensor
    if(!(isSensorA ^ isSensorB)) return false;

    if(isSensorA){
      radarEntity = static_cast<Ball4 *>(fixtureA->GetBody()->GetUserData());
      aircraftEntity = static_cast<Ball4 *>(fixtureB->GetBody()->GetUserData());
    } else {
      radarEntity = static_cast<Ball4 *>(fixtureB->GetBody()->GetUserData());
      aircraftEntity = static_cast<Ball4 *>(fixtureA->GetBody()->GetUserData());
    }
    return true;
  }
};

#endif
