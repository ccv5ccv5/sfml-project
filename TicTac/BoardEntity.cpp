#include "BoardEntity.h"

BoardEntity::BoardEntity(float width, float height){
  for(int i = 0; i < NUM_SPACES; ++i){
    board[i] = EMPTY;
  }

  pieces = new Array<sf::RectangleShape>();
  num_spaces = NUM_SPACES;

  //create the visible board
  sf::RectangleShape *piece;
  for(int c = 0; c < NUM_COLS; ++c){
    for(int r = 0; r < NUM_ROWS; ++r){
      piece = new sf::RectangleShape(sf::Vector2f(width/NUM_COLS, height/NUM_ROWS));  
      piece->setFillColor(sf::Color::Transparent);
      piece->setOutlineThickness(3);
      piece->setPosition(r * (width/NUM_COLS), c * (height/NUM_ROWS));
      pieces->add(piece);
    }
  }

}

bool BoardEntity::place(CircleEntity *circ, int x, int y){
  sf::RectangleShape *piece;
  sf::Vector2f size, position;
  float thickness = circ->getOutlineThickness();

  for(int i = 0; i < pieces->size(); ++i){
    piece = pieces->get(i);
    position = piece->getPosition();
    size = piece->getSize();

    //If the circle intersects with one of the pieces
    if(x > position.x && x < (position.x + size.x)) {
      if(y > position.y && y < (position.y + size.y)) {

	//And there is nothing in that spot, place it
	if(board[i] == EMPTY){
	  board[i] = CIRCLE;

	  if(size.x < size.y)
	    circ->setRadius(size.x / 2 - thickness);
	  else
	    circ->setRadius(size.y / 2 - thickness);

	  circ->setPosition(position.x + thickness, 
			    position.y + thickness);
	  num_spaces--;
	  return true;
	}
      }
    }
  }

  return false;
}

bool BoardEntity::place(CrossEntity *cross, int x, int y){
  sf::RectangleShape *piece;
  sf::Vector2f size, position;

  for(int i = 0; i < pieces->size(); ++i){
    piece = pieces->get(i);
    position = piece->getPosition();
    size = piece->getSize();

    //If the circle intersects with one of the pieces
    if(x > position.x && x < (position.x + size.x)) {
      if(y > position.y && y < (position.y + size.y)) {

	//And there is nothing in that spot, place it
	if(board[i] == EMPTY){
	  board[i] = CROSS;

	  cross->setPosition(position.x, position.y);
	  num_spaces--;
	  return true;
	}
      }
    }
  }

  return false;
}

int BoardEntity::winner(){
  int winner = NO_WIN;

  //check rows for win
  for(int i = 0; i < NUM_SPACES; i+=3){
    winner = board[i] + board[i + 1] + board[i + 2];
    if(winner == PLAYER_ONE_WIN)
      return PLAYER_ONE;
    if(winner == PLAYER_TWO_WIN)
      return PLAYER_TWO;
  }

  //check cols for win
  for(int i = 0; i < 3; ++i){
    winner = board[i] + board[i + 3] + board[i + 6];
    if(winner == PLAYER_ONE_WIN)
      return PLAYER_ONE;
    if(winner == PLAYER_TWO_WIN)
      return PLAYER_TWO;
  }

  //check diags for win
  winner = board[0] + board[4] + board[8];
  if(winner == PLAYER_ONE_WIN)
      return PLAYER_ONE;
    if(winner == PLAYER_TWO_WIN)
      return PLAYER_TWO;

  winner = board[2] + board[4] + board[6];
  if(winner == PLAYER_ONE_WIN)
    return PLAYER_ONE;
  if(winner == PLAYER_TWO_WIN)
    return PLAYER_TWO;
  
  //If there are no spaces left, but no one won,
  //it must be a draw
  if(num_spaces == 0)
    return DRAW;
  return NO_WIN;
}

void BoardEntity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(int i = 0; i < pieces->size(); ++i)
      target.draw(*(pieces->get(i)), states);
}

BoardEntity::~BoardEntity(){
  if(pieces != NULL)
    delete pieces;
}
