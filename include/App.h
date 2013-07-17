#ifndef _APP_H_
#define _APP_H_

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

namespace DAN {

  class App {
  public:
    /*
     * Constructs an App for use
     *
     * @params width: width of the window
     *         height: height of the window
     *         title: title of window in titlebar
     */
    App(int width, int height, string title);
    ~App();
    
    // Runs the entire App
    void run();
    
    // Initializes necessary items at start of the App
    void onInit();

    // Does whatever is necessary upon closing the window
    void onClose();

    // Does whatever is necessary upon exit of the App
    void onExit();
    
    // The game loop. Calls all functions for game logic, display, etc.
    void loop();
    
    // Polls events from the window and calls appropriate functions
    void pollEvents();
    
    // Renders items to the window
    void render();

  private:
    // Pointer to the window that must be drawn
    sf::RenderWindow *m_window;

    // Is the App currently running?
    bool m_is_running;

    // Details for the window
    int m_width, m_height;
    string m_title;
  };
}

#endif
