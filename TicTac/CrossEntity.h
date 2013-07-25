#ifndef __CROSS_ENTITY_H__
#define __CROSS_ENTITY_H__

#include "../include/BasicEntity.h"
#include <cmath>

using namespace std;
using namespace DAN;

class CrossEntity : public BasicEntity {
 public:
  CrossEntity(int width, int height);
  void setPosition(float x, float y);

  void setFillColor(sf::Color c);
 private:
  sf::RectangleShape line_parts[2];

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(line_parts[0], states);
    target.draw(line_parts[1], states);
  }
};

#endif
