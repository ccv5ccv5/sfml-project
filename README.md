## Project to learn SFML and Box2D ##

No idea what will come out of this, but it is something to kill the time.

If anyone wants to use these files, they will need to build SFML themeselves.
Just to note, one needs knowledge of C++ to use SFML and this version of Box2D.

### SFML ###

SFML can be found [here](http://www.sfml-dev.org/download/sfml/2.0/).
Used [this tutorial](http://sfmlcoder.wordpress.com/2011/08/16/building-sfml-2-0-with-make-for-gcc/) to assist/tell me how to build it on Ubuntu.

### Box2D ###

Box2D can be found [here](https://code.google.com/p/box2d/).
The setup tutorial I used is found [here](http://www.iforce2d.net/b2dtut/setup-linux). It also contains links for setup on Windows and Mac.

### Current Plan ###

Creating an engine for a simple Tic-Tac-Toe game.

#### Goals of Current Plan ####

- Writing a sizable piece of software.
- C++ practice
- Practice with writing a basic engine (render, interaction, game logic)
- git practice

##### Current Tasks #####
```
- [x] Create Basic Entity super class for organizing renderable items
- [x] Implement Array class (with Template?)
- [ ] Move current example code out of App.cpp into subclass
- [ ] Create and render game board
- [ ] Enhance example to allow circles to only be placed in certain locations
- [ ] Create a Cross Entity
- [ ] Determine win state (board logic?)
```
### Steps After Current Plan ###

- Experiment with Box2D
- Expand to Pong (animations, collisions, time)
