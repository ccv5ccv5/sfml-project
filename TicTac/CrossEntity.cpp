#include "CrossEntity.h"

CrossEntity::CrossEntity(int width, int height){
  float length = sqrt((width * width) + (height * height));
  line_parts[0].setSize(sf::Vector2f(length, 5));
  line_parts[0].rotate(45);
  line_parts[1].setSize(sf::Vector2f(5, length));
  line_parts[1].setPosition(width, 0);
  line_parts[1].rotate(45);
}

void CrossEntity::setPosition(float x, float y){
  float width = line_parts[1].getPosition().x - line_parts[0].getPosition().x;
  line_parts[0].setPosition(x, y);
  line_parts[1].setPosition(x + width, y);
}

void CrossEntity::setFillColor(sf::Color c){
  line_parts[0].setFillColor(c);
  line_parts[1].setFillColor(c);
}
