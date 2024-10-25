#include <utility>
#include <stdexcept>
#include <ranges>
#include <SFML/Graphics/RectangleShape.hpp>
#include <snake.h>
#include <direction.h>

namespace snake {

template<typename T = float>
inline constexpr T tile_size = static_cast<T>(100);

snake::snake(sf::Vector2i head, std::size_t length)
    :head_{head} {
    if (length == 0zu) {
        throw std::invalid_argument{"snake must have a non-zero length"};
    }

    for (auto _ : std::views::iota(0zu, length - 1zu)) {
        grow(direction::right);
    }
}

void snake::move(direction dir) {
    grow(dir);
    if (!tail_.empty()) {
        tail_.pop_back();
    }
}

void snake::grow(direction dir) {
    auto delta = to_vec<int>(dir);
    // row-major indices
    std::swap(delta.x, delta.y);
    head_ += delta;
    tail_.push_front(dir);
}

void snake::pop_tail() {
    tail_.clear();
}

std::size_t snake::length() const {
    // tail + head
    return tail_.size() + 1;
}

sf::Vector2i snake::head() const {
    return head_;
}

}

