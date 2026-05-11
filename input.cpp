#include "input.h"

Command Key_input::get_input(sf::RenderWindow& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window.close();
    }
    if (event.type == sf::Event::KeyPressed) {
      switch (event.key.code) {
      case sf::Keyboard::W:       return Command::MOVE_UP;
      case sf::Keyboard::S:       return Command::MOVE_DOWN;
      case sf::Keyboard::A:       return Command::MOVE_LEFT;
      case sf::Keyboard::D:       return Command::MOVE_RIGHT;
      case sf::Keyboard::E:       return Command::GET_INFO;
      case sf::Keyboard::Space:   return Command::SELL;
      }
    }
  }
}