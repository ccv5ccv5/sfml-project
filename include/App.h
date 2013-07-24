#ifndef _APP_H_
#define _APP_H_

/**
 *  Base App class for use in any extension of the engine.
 *  Built using SFML 2.0.
 *
 *  (c)2013 Diogenes A. Nunez
 */

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "../src/Array.cpp"

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
    virtual void onInit();

    // Does whatever is necessary upon closing the window
    virtual void onClose();

    // Does whatever is necessary upon exit of the App
    virtual void onExit();
    
    // The game loop. Calls all functions for game logic, display, etc.
    void loop();
    
    // Polls events from the window and calls appropriate functions
    void pollEvents();
    
    virtual void onMousePress(sf::Event event) { }

    // Renders items to the window
    virtual void render(sf::RenderWindow *window) { }

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
