#include <SFML/Graphics/RectangleShape.hpp>
#include <snake.h>
#include <direction.h>

namespace snake {

template<typename T = float>
inline constexpr T tile_size = static_cast<T>(100);

snake::snake(sf::Vector2i head)
    :head_{head} {}

void snake::move(direction dir) {
    if (!tail_.empty()) {
        tail_.pop_back();
    }
    grow(dir);
}

void snake::grow(direction dir) {
    head_ += to_vec<int>(dir);
    tail_.push_front(dir);
}

void snake::draw([[maybe_unused]] sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const {
    const sf::Vector2u window_size{target.getSize()};
    sf::Vector2i pos{head_};
    sf::RectangleShape segment{sf::Vector2f{tile_size<float>, tile_size<float>}};
    
    segment.setPosition(pos.x, pos.y);
    target.draw(segment, states);

    for (direction dir : tail_) {
        // render tiles in opposite direction
        sf::Vector2i offset = -1 * to_vec<int>(dir);
        
        if (pos.x == 0 && offset.x < 0) {
            pos.x += window_size.x;
        }

        if (pos.x == window_size - tile_size<float> && offset.x < 0) {
            pos.x += window_size.x;
        }

        segment.move(offset.x, offset.y);
        target.draw(segment, states);
    }
}

}

