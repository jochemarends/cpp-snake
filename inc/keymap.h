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
    .up = sf::Keyboard::Key::K,
    .down = sf::Keyboard::Key::J,
    .left = sf::Keyboard::Key::H,
    .right = sf::Keyboard::Key::L,
};

constexpr keymap wasd_keymap{
    .up = sf::Keyboard::Key::W,
    .down = sf::Keyboard::Key::S,
    .left = sf::Keyboard::Key::A,
    .right = sf::Keyboard::Key::D,
};

constexpr keymap arrow_keymap{
    .up = sf::Keyboard::Key::Up,
    .down = sf::Keyboard::Key::Down,
    .left = sf::Keyboard::Key::Left,
    .right = sf::Keyboard::Key::Right,
};

}

#endif

