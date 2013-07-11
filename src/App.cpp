#include "../include/App.h"

App::App(sf::RenderWindow *window){
  m_window = window;
}

void App::onInit(){

}

void App::run(){
  onInit();

  while(m_window->isOpen()){

    //poll Events

    //render

  }
}

App::~App(){

}
