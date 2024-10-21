#include <game.h>
#include <algorithm>
#include <optional>
#include <random>

namespace snake {

game::game(keymap keymap)
    :keymap_{keymap} {
    spawn_apple();
    draw();
}

void game::tick() {
    snake_.move(direction_);
    handle_collisions();
    draw();
}

void game::draw() {
    grid_.clear();
    snake_.draw(grid_);

    for (apple apple : apples_) {
        apple.draw(grid_);
    }
}

void game::handle_collisions() {
    std::vector<sf::Vector2<std::size_t>> snake_indices{};
    snake_.copy_indices<game::rows_, game::columns_>(std::back_inserter(snake_indices));

    // handle head with tail collisions
    sf::Vector2<std::size_t> head_index{snake_indices.front()};
    if (std::ranges::count(snake_indices, head_index) > 1) {
        // TODO: end game
    }

    // handle snake with apple collisions
    for (sf::Vector2<std::size_t> snake_index : snake_indices) {
        sf::Vector2i position(snake_index);
        if (auto it = std::ranges::find(apples_, position, &apple::position); it != apples_.end()) {
            snake_.grow(direction_);
            apples_.erase(it);
        }
    }
}

void game::handle_event(const sf::Event& e) {
    if (e.type == sf::Event::KeyPressed) {
        std::optional<direction> input_direction{};

        if (e.key.code == keymap_.up) {
            input_direction = direction::up;
        }
        if (e.key.code == keymap_.down) {
            input_direction = direction::down;
        }
        if (e.key.code == keymap_.left) {
            input_direction = direction::left;
        }
        if (e.key.code == keymap_.right) {
            input_direction = direction::right;
        }

        if (input_direction.has_value()) {
            // the snake cannot make a 180 degree turn
            if (to_vec<int>(input_direction.value()) != -1 * to_vec<int>(direction_)) {
                direction_ = input_direction.value();
            }
        }
    }
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(grid_, states);
}

void game::spawn_apple() {
    std::random_device dev{};
    std::mt19937 rng{dev()};
    std::uniform_int_distribution row_dist{0zu, game::columns_ - 1zu};
    std::uniform_int_distribution column_dist{0zu, game::columns_ - 1zu};

    sf::Vector2<std::size_t> index{};
    index.x = row_dist(rng);
    index.y = column_dist(rng);

    // position must not be occupies yet
    if (grid_[index.x, index.y] != sf::Color::Transparent) {
        spawn_apple();
    }
    else {
        apples_.emplace_back(sf::Vector2i(index));
    }
};

}

