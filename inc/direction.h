#ifndef DIRECTION_H
#define DIRECTION_H

#include <SFML/System/Vector2.hpp>

namespace snake {

enum class direction {
    up, 
    down,
    left, 
    right,
};

template<typename T = float>
constexpr sf::Vector2<T> to_vec(direction dir) {
    sf::Vector2<T> res{};

    switch (dir) {
    case direction::up:
        --res.y = static_cast<T>(-1);
        break;
    case direction::down:
        res.y = static_cast<T>(1);
    case direction::left:
        res.x = static_cast<T>(-1);
        break;
    case direction::right:
        res.x = static_cast<T>(1);
    }

    return res;
}

}

#endif

