#include "../include/App.h"

namespace DAN{
  App::App(sf::RenderWindow *window){
    m_window = window;
  }

  void App::onInit(){
    
  }
  
  void App::run(){
    onInit();

    loop();
  }

  void App::loop(){
    while(m_window->isOpen()){
      
      pollEvents();
      
      render();
      
    }
  }
  
  void App::pollEvents(){
    
  }
  
  void App::render(){
    
  }
  
  App::~App(){

  }
}
