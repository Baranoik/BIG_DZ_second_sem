#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

enum class Command {
    NONE,
    GET_INFO,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SELL
};

class Key_input {
public:
    Command get_input(sf::RenderWindow& window);
};

#endif // INPUT_H
