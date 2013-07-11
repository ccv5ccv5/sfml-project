#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <SFML/Graphics.hpp>

class App {
 public:
  App(sf::RenderWindow *window);
  void onInit();
  void run();
  ~App();
 private:
  sf::RenderWindow *m_window;
};

#endif
