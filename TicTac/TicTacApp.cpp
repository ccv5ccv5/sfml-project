#include "TicTacApp.h"

using namespace DAN;

void TicTacApp::onInit(){
  App::onInit();
  m_basic = new Array<BasicEntity>();
}

void TicTacApp::onClose(){
  App::onClose();
}

void TicTacApp::onExit(){
  delete m_basic;
  m_basic = NULL;

  App::onExit();
}

void TicTacApp::onMousePress(sf::Event event){
  if(m_basic->size() == 9)
    m_basic->remove(0);

  CircleEntity *circ = new CircleEntity(10);
  circ->setPosition(event.mouseButton.x, event.mouseButton.y);
  circ->setFillColor(sf::Color::Green);
  m_basic->add(circ);
}

void TicTacApp::render(sf::RenderWindow *window){
    // Insert rendering statements here
    for(int i = 0; i < m_basic->size(); ++i){
      window->draw(*(m_basic->get(i)));
    }
}

TicTacApp::~TicTacApp() {
  if(m_basic != NULL){
    delete m_basic;
    m_basic = NULL;
  }
}
