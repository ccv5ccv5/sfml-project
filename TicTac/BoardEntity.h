#ifndef __BOARD_ENTITY_H__
#define __BOARD_ENTITY_H__

#include "../include/BasicEntity.h"
#include "CircleEntity.h"
#include "CrossEntity.h"
#include "../src/Array.cpp"

using namespace DAN;

class BoardEntity : public BasicEntity {
 public:
  BoardEntity(float, float);
  ~BoardEntity();
  bool place(CircleEntity *circ, int x, int y);
  bool place(CrossEntity *circ, int x, int y);
  int winner();

  static const int NUM_SPACES = 9;
  static const int NUM_ROWS = 3;
  static const int NUM_COLS = 3;

  static const int PLAYER_ONE = 0;
  static const int PLAYER_TWO = 1;
  static const int DRAW = -2;
 private:
  Array<sf::RectangleShape> *pieces;
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  int board[NUM_SPACES];

  static const int EMPTY = 0;
  static const int CIRCLE = 1;
  static const int CROSS = -1;
  static const int PLAYER_ONE_WIN = 3;
  static const int PLAYER_TWO_WIN = -3;
  static const int NO_WIN = -1;

  int num_spaces;
};

#endif
