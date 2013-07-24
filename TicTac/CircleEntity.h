#ifndef __CIRCLE_ENTITY_H__
#define __CIRCLE_ENTITY_H__

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "../include/BasicEntity.h"

using namespace std;

namespace DAN {

  class CircleEntity : public BasicEntity {
  public:
    CircleEntity(float radius);
    void setPosition(float x, float y);
    float getX() { return circle.getPosition().x; }
    float getRadius() { return circle.getRadius(); }
    void setFillColor(sf::Color c);

  private:
    sf::CircleShape circle;

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
      target.draw(circle, states);
    }
  };

}

#endif
