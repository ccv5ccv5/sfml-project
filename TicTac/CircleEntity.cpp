#include "CircleEntity.h"

CircleEntity::CircleEntity(float radius){
  circle.setRadius(radius);
}

void CircleEntity::setPosition(float x, float y){
  circle.setPosition(x, y);
}

void CircleEntity::setRadius(float radius){
  circle.setRadius(radius);
}

void CircleEntity::setFillColor(sf::Color c){
  circle.setFillColor(c);
}

void CircleEntity::setOutlineColor(sf::Color c){
  circle.setOutlineColor(c);
}

void CircleEntity::setOutlineThickness(float thickness){
  circle.setOutlineThickness(thickness);
}

float CircleEntity::getOutlineThickness(){
  return circle.getOutlineThickness();
}

