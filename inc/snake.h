#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <direction.h>
#include <grid.h>

namespace snake {

struct snake {
    explicit snake(sf::Vector2i head);

    void move(direction dir);
    void grow(direction dir);
    void draw(const grid& grid) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private: 
    sf::Vector2i head_{};
    std::deque<direction> tail_{};
};

}

#endif

