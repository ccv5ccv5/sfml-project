#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <SFML/Graphics.hpp>

namespace DAN {

  class App {
  public:
    App(sf::RenderWindow *window);
    ~App();
    
    // Runs the entire App
    void run();
    
    // Initializes necessary items
    void onInit();
    
    // The game loop
    void loop();
    
    // Polls events from the window and calls appropriate functions
    void pollEvents();
    
    // Renders items to the window
    void render();

  private:
    sf::RenderWindow *m_window;
  };
}

#endif
