#ifndef __TIC_TAC_APP_H__
#define __TIC_TAC_APP_H__

/**
 *  Main class for TicTacToe game using basic engine.
 *
 *  (c) 2013 Diogenes A. Nunez
 */

#include "../include/App.h"

using namespace DAN;

class TicTacApp : public App {
 public:
 TicTacApp(int width, int height, string title) : App(width, height, title) { }
  ~TicTacApp();

  virtual void onInit();
  virtual void onClose();
  virtual void onExit();
  virtual void onMousePress(sf::Event event);
  virtual void render(sf::RenderWindow *window);
 
 private:
  Array<BasicEntity> *m_basic;
};

#endif
