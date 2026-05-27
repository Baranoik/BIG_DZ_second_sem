#include "input.h"
#include <optional>

Command Key_input::get_input(sf::RenderWindow& window) {
  // В SFML 3 метод pollEvent() не принимает аргументов и возвращает std::optional
  while (const std::optional<sf::Event> event = window.pollEvent()) {
    
    // Проверка закрытия окна через метод ->is
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
    
    // Проверка нажатия клавиши и извлечение её кода
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      switch (keyPressed->code) {
        case sf::Keyboard::Key::W:       return Command::MOVE_UP;
        case sf::Keyboard::Key::S:       return Command::MOVE_DOWN;
        case sf::Keyboard::Key::A:       return Command::MOVE_LEFT;
        case sf::Keyboard::Key::D:       return Command::MOVE_RIGHT;
        case sf::Keyboard::Key::E:       return Command::GET_INFO;
        case sf::Keyboard::Key::Space:   return Command::SELL;
        default:                         break; 
      }
    }
  }
  return Command::GET_INFO; 
}
