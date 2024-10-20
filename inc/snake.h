#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <direction.h>
#include <grid.h>
#include <utility.h>

namespace snake {

struct snake {
    static inline const sf::Color color{sf::Color::Green};

    explicit snake(sf::Vector2i head, std::size_t length = 1);

    /**
     * Move the snake one step in a direction.
     *
     * @param dir Direction to move the snake's head to.
     */
    void move(direction dir);

    /**
     * Grow the snake one step in a direction
     *
     * @param dir Direction to grow the snake's head to.
     */
    void grow(direction dir);

    /**
    * Draw the snake on a grid.
    * 
    * @parm grid Grid to draw the snake on.
    */
    template<std::size_t Rows, std::size_t Columns>
    void draw(grid<Rows, Columns>& grid) const;
private: 
    sf::Vector2i head_{};
    std::deque<direction> tail_{};
};

template<std::size_t Rows, std::size_t Columns>
void snake::draw(grid<Rows, Columns>& grid) const {
    const auto [rows, columns] = grid.dims();

    sf::Vector2i pos{head_};
    // map the head to a valid grid index
    pos.x = wrap<int>(pos.x, 0, rows - 1);
    pos.y = wrap<int>(pos.y, 0, columns - 1);
    grid.fill(sf::Vector2<std::size_t>(pos), snake::color);
    
    for (direction dir : tail_) {
        // render tiles in opposite direction
        sf::Vector2 offset = -1 * to_vec<int, layout::row_major>(dir);

        // map the position to a valid grid index
        pos.x = wrap<int>(pos.x + offset.x, 0, rows - 1);
        pos.y = wrap<int>(pos.y + offset.y, 0, columns - 1);

        grid.fill(sf::Vector2<std::size_t>(pos), snake::color);
    }
}

}

#endif

