#ifndef KEY_MAP_H
#define KEY_MAP_H

#include <SFML/Window/Keyboard.hpp>

namespace snake {

struct keymap {
    sf::Keyboard::Key up;
    sf::Keyboard::Key down;
    sf::Keyboard::Key left;
    sf::Keyboard::Key right;
};

constexpr keymap vi_keymap{
    .up = sf::Keyboard::K,
    .down = sf::Keyboard::J,
    .left = sf::Keyboard::H,
    .right = sf::Keyboard::L,
};

constexpr keymap wasd_keymap{
    .up = sf::Keyboard::W,
    .down = sf::Keyboard::S,
    .left = sf::Keyboard::A,
    .right = sf::Keyboard::D,
};

constexpr keymap arrow_keymap{
    .up = sf::Keyboard::Up,
    .down = sf::Keyboard::Down,
    .left = sf::Keyboard::Left,
    .right = sf::Keyboard::Right,
};

}

#endif

