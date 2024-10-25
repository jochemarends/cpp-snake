#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <iterator>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <direction.h>
#include <grid.h>
#include <utility.h>
#include <vector>

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

    void pop_tail();

    /**
     * Obtain the length of the snake in tiles.
     */
    std::size_t length() const;

    /**
     * Obtain the position of the the snake's head.
     */
    sf::Vector2i head() const;

    /**
    * Draw the snake on a grid.
    * 
    * @param grid Grid to draw the snake on.
    */
    template<std::size_t Rows, std::size_t Columns>
    void draw(grid<Rows, Columns>& grid) const;

    /**
    * Obtain the indices the snake would occupy on a certain grid.
    *
    * @param out Output iterator where indices will be written to.
    */
    template<std::size_t Rows, std::size_t Columns, std::output_iterator<sf::Vector2<std::size_t>> OutputIt>
    void copy_indices(OutputIt out) const;
private: 
    sf::Vector2i head_{};
    std::deque<direction> tail_{};
};

template<std::size_t Rows, std::size_t Columns>
void snake::draw(grid<Rows, Columns>& grid) const {
    sf::Vector2i pos{head_};

    // map the head to a valid grid index
    pos.x = wrap<int>(pos.x, 0, Rows - 1);
    pos.y = wrap<int>(pos.y, 0, Columns - 1);
    grid.fill(sf::Vector2<std::size_t>(pos), snake::color);
    
    std::vector<sf::Vector2<std::size_t>> indices{};
    copy_indices<Rows, Columns>(std::back_inserter(indices));

    for (sf::Vector2<std::size_t> index : indices) {
        grid.fill(index, snake::color);
    }
}

template<std::size_t Rows, std::size_t Columns, std::output_iterator<sf::Vector2<std::size_t>> OutputIt>
void snake::copy_indices(OutputIt out) const {
    sf::Vector2i index{head_};

    // map the position to a valid grid index
    index.x = wrap<int>(index.x, 0, Rows - 1);
    index.y = wrap<int>(index.y, 0, Columns - 1);

    out++ = sf::Vector2<std::size_t>(index);

    for (direction dir : tail_) {
        // render tiles in opposite direction
        index += -1 * to_vec<int, layout::row_major>(dir);

        // map the position to a valid grid index
        index.x = wrap<int>(index.x, 0, Rows - 1);
        index.y = wrap<int>(index.y, 0, Columns - 1);

        out++ = sf::Vector2<std::size_t>(index);
    }
}
    
}

#endif

