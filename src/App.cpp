#include "../include/App.h"

using namespace std;

namespace DAN{
  App::App(int width, int height, string title){
    m_width = width;
    m_height = height;
    m_title = title;
    m_is_running = false;
  }

  void App::onInit(){
    m_window = new sf::RenderWindow(sf::VideoMode(m_width, m_height), m_title);
    m_is_running = true;
  }
  
  void App::onClose(){
    m_is_running = false;
    m_window->close();
  }

  void App::onExit(){
    delete m_window;
    m_window = NULL;
  }

  void App::run(){
    // Initialize necessary components
    onInit();

    loop();

    // Destroy components no longer required
    onExit();
  }

  void App::loop(){
    while(m_window->isOpen()){
      
      pollEvents();
      
      if(m_is_running) render();
    }
  }
  
  void App::pollEvents(){
    sf::Event event;
    while(m_window->pollEvent(event)){
      if(event.type == sf::Event::Closed) onClose();
    }
  }
  
  void App::render(){
    m_window->clear();

    // Insert rendering statements here

    m_window->display();
  }
  
  App::~App(){
    // Stop window if it is still running
    if(m_is_running && m_window != NULL) {
      m_window->close();
    }

    // Remove all malloc'd memory
    if(m_window != NULL){
      delete m_window;
      m_window = NULL;
    }
  }
}
