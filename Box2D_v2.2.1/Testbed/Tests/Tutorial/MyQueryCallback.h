#ifndef __MY_QUERY_CALLBACK_H__
#define __MY_QUERY_CALLBACK_H__

#include <vector>

//Callback for AABB queries
class MyQueryCallback : public b2QueryCallback {
 public:
  std::vector<b2Body*> foundBodies;
  bool ReportFixture(b2Fixture *fixture){
    foundBodies.push_back(fixture->GetBody());
    return true;
  }
};

#endif
