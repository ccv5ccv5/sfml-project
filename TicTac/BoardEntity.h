#ifndef __BOARD_ENTITY_H__
#define __BOARD_ENTITY_H__

#include "../include/BasicEntity.h"
#include "../src/Array.cpp"

using namespace DAN;

class BoardEntity : public BasicEntity {
 public:
  BoardEntity(float, float);
  ~BoardEntity();
 private:
  Array<sf::RectangleShape> *pieces;
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif
