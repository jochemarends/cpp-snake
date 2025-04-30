#ifndef APPLE_H
#define APPLE_H

#include <SFML/Graphics/Color.hpp>
#include <grid.h>
#include <utility.h>

namespace snake {

struct apple {
    static inline const sf::Color color{sf::Color::Red};

    apple(sf::Vector2i position);

    /**
    * Draw the apple on a grid.
    * 
    * @param grid Grid to draw the apple on.
    */
    template<std::size_t Rows, std::size_t Columns>
    void draw(grid<Rows, Columns>& grid) const;

    sf::Vector2i position{};
};

template<std::size_t Rows, std::size_t Columns>
void apple::draw(grid<Rows, Columns>& grid) const {
    sf::Vector2i index{position};

    // map the position to a valid grid index
    index.x = wrap<int>(index.x, 0, Rows - 1);
    index.y = wrap<int>(index.y, 0, Columns - 1);

    grid.fill(sf::Vector2<std::size_t>(index), apple::color);
}

}

#endif

