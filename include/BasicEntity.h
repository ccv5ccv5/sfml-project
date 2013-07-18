#ifndef __BASIC_ENTITY_H__
#define __BASIC_ENTITY_H__

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

namespace DAN {
  class BasicEntity : public sf::Drawable , public sf::Transformable{
  public:
  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const{ }
  };

}

#endif
