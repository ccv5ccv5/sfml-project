#include "CircleEntity.h"

namespace DAN{
  CircleEntity::CircleEntity(float radius){
    circle.setRadius(radius);
  }

  void CircleEntity::setPosition(float x, float y){
    circle.setPosition(x, y);
  }

  void CircleEntity::setFillColor(sf::Color c){
    circle.setFillColor(c);
  }

}
