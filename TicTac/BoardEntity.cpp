#include "BoardEntity.h"

BoardEntity::BoardEntity(float width, float height){
  pieces = new Array<sf::RectangleShape>();

  sf::RectangleShape *piece = new sf::RectangleShape(sf::Vector2f(20, height));
  piece->setPosition(sf::Vector2f(width/3.0 - 10, 0));
  pieces->add(piece);

  piece = new sf::RectangleShape(sf::Vector2f(20, height));
  piece->setPosition(sf::Vector2f((width/3.0) * 2 - 10, 0));
  pieces->add(piece);

  piece = new sf::RectangleShape(sf::Vector2f(width, 20));
  piece->setPosition(sf::Vector2f(0, height/3.0 - 10));
  pieces->add(piece);

  piece = new sf::RectangleShape(sf::Vector2f(width, 20));
  piece->setPosition(sf::Vector2f(0, (height/3.0) * 2 - 10));
  pieces->add(piece);
}

void BoardEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(int i = 0; i < pieces->size(); ++i)
      target.draw(*(pieces->get(i)), states);
}

BoardEntity::~BoardEntity(){
  if(pieces != NULL)
    delete pieces;
}
