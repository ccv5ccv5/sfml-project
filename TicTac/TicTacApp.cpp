#include "TicTacApp.h"

using namespace DAN;

void TicTacApp::onInit(){
  App::onInit();
  m_basic = new Array<BasicEntity>();

  m_board = new BoardEntity(m_width, m_height);
}

void TicTacApp::onClose(){
  App::onClose();
}

void TicTacApp::onExit(){
  delete m_basic;
  m_basic = NULL;
  
  delete m_board;
  m_board = NULL;

  App::onExit();
}

void TicTacApp::onMousePress(sf::Event event){
  //Do nothing if the game is won
  if(m_done) return;

  if(m_player % 2 == 0){
    CircleEntity *circ = new CircleEntity(20);
    circ->setOutlineThickness(3);
    circ->setOutlineColor(sf::Color::Red);
    circ->setFillColor(sf::Color::Transparent);

    //If we can place the circle there, add it to the entity list
    if(m_board->place(circ, event.mouseButton.x, event.mouseButton.y)){
      m_basic->add(circ);
      m_player++;
    }
  } else {
    CrossEntity *cross = new CrossEntity(m_width/3.0, m_height/3.0);
    cross->setFillColor(sf::Color::Blue);

    //If we can place the cross there, add it to the entity list
    if(m_board->place(cross, event.mouseButton.x, event.mouseButton.y)){
      m_basic->add(cross);
      m_player++;
    }
  }
}

void TicTacApp::update(){
  int winner = m_board->winner();
  if(winner >= 0 || winner == BoardEntity::DRAW)
    m_done = true;
  if(winner == BoardEntity::PLAYER_ONE)
    m_title = "Player 1 wins!";
  else if (winner == BoardEntity::PLAYER_TWO)
    m_title = "Player 2 wins!";
  else if (winner == BoardEntity::DRAW)
    m_title = "Draw!";
}

void TicTacApp::render(sf::RenderWindow *window){
  //Change the title of the window when the game is over
  if(m_done)
    window->setTitle(m_title);

  //Render the crosses and circles
  for(int i = 0; i < m_basic->size(); ++i){
    window->draw(*(m_basic->get(i)));
  }

  //Render the board to hide any ugliness from the pieces
  window->draw(*m_board);
}

TicTacApp::~TicTacApp() {
  if(m_basic != NULL){
    delete m_basic;
    m_basic = NULL;
  }
}
