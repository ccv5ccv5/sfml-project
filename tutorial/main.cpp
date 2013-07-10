#include <SFML/Graphics.hpp>

int main(){

  //Create window of a w,h resolution with title
  sf::RenderWindow window(sf::VideoMode(200,200), "SFML Works");

  //Create green circle
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);
  
  //Main loop for window
  while(window.isOpen()){
    sf::Event event;

    //Main event loop
    while(window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
	window.close();
      }
    }

    //Render information [Essentially render loop]
    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}
