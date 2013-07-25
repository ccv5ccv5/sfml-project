#ifndef __CIRCLE_ENTITY_H__
#define __CIRCLE_ENTITY_H__

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "../include/BasicEntity.h"

using namespace std;
using namespace DAN;

class CircleEntity : public BasicEntity {
 public:
  CircleEntity(float radius);
  void setPosition(float x, float y);
  
  void setRadius(float radius);
  float getRadius() { return circle.getRadius(); }
  
  void setFillColor(sf::Color c);
  void setOutlineColor(sf::Color c);
  
  void setOutlineThickness(float thickness);
  float getOutlineThickness();
  
  private:
  sf::CircleShape circle;
  
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(circle, states);
  }
};

#endif
