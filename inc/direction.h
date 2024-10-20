#ifndef DIRECTION_H
#define DIRECTION_H

#include <string_view>
#include <utility>
#include <SFML/System/Vector2.hpp>
#include <utility.h>

namespace snake {

enum class direction {
    up, 
    down,
    left, 
    right,
};

template<typename T = float, layout L = layout::column_major>
constexpr sf::Vector2<T> to_vec(direction dir) {
    sf::Vector2<T> res{};

    switch (dir) {
    case direction::up:
        res.y = static_cast<T>(-1);
        break;
    case direction::down:
        res.y = static_cast<T>(1);
        break;
    case direction::left:
        res.x = static_cast<T>(-1);
        break;
    case direction::right:
        res.x = static_cast<T>(1);
        break;
    }

    if constexpr (L == layout::row_major) {
        std::swap(res.x, res.y);
    }

    return res;
}

}

#endif

