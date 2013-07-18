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

    m_basic = new BasicEntity* [10];

    m_capacity = 10;
    m_num_entities = 0;

    for(int i = 0; i < m_capacity; ++i)
      m_basic[i] = NULL;
  }
  
  void App::onClose(){
    m_is_running = false;
    m_window->close();
  }

  void App::onExit(){

    for(int i = 0; i < m_capacity; ++i){
      if(m_basic[i] != NULL) delete m_basic[i];
      m_basic[i] = NULL;
    }

    delete [] m_basic;
    m_basic = NULL;

    m_capacity = 0;
    m_num_entities = 0;

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
      if(event.type == sf::Event::MouseButtonPressed) onMousePress(event);
    }
  }

  void App::onMousePress(sf::Event event){
    int index = m_num_entities % m_capacity;

    if(m_num_entities >= m_capacity)
      delete m_basic[index];

    CircleEntity *circ = new CircleEntity(10);
    circ->setPosition(event.mouseButton.x, event.mouseButton.y);
    circ->setFillColor(sf::Color::Green);
    m_basic[index] = circ;
    
    m_num_entities++;

  }
  
  void App::render(){
    m_window->clear();

    // Insert rendering statements here
    for(int i = 0; i < m_num_entities && i < m_capacity; ++i){
      m_window->draw(*(m_basic[i]));
    }

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
