#include <level.h>
#include <random>

namespace snake {
    
level::level(sf::Vector2f top_left)
    :grid_{top_left, level::tile_size} {
    spawn_apple();
    draw();
}

void level::tick() {
    if (!is_dead_) {
        curr_direction_ = next_direction_;
        // move with wraparound
        snake_.move(curr_direction_);
        handle_collisions();
        draw();
    }
}

void level::draw() {
    grid_.clear();
    snake_.draw(grid_);

    for (apple apple : apples_) {
        apple.draw(grid_);
    }
}

void level::handle_collisions() {
    std::vector<sf::Vector2<std::size_t>> snake_indices{};
    snake_.copy_indices<level::rows, level::columns>(std::back_inserter(snake_indices));

    // handle head with tail collisions
    sf::Vector2<std::size_t> head_index{snake_indices.front()};
    if (std::ranges::count(snake_indices, head_index) > 1) {
        die();
    }

    // handle snake with apple collisions
    for (sf::Vector2<std::size_t> snake_index : snake_indices) {
        sf::Vector2i position(snake_index);
        if (auto it = std::ranges::find(apples_, position, &apple::position); it != apples_.end()) {
            snake_.grow(curr_direction_);
            apples_.erase(it);
            spawn_apple();
        }
    }
}

void level::handle_event(const sf::Event& e, const keymap& keymap) {
    if (is_dead_) {
        return;
    }

    if (e.type == sf::Event::KeyPressed) {
        std::optional<direction> input_direction{};

        if (e.key.code == keymap.up) {
            input_direction = direction::up;
        }
        else if (e.key.code == keymap.down) {
            input_direction = direction::down;
        }
        else if (e.key.code == keymap.left) {
            input_direction = direction::left;
        }
        else if (e.key.code == keymap.right) {
            input_direction = direction::right;
        }

        if (input_direction.has_value()) {
            // the snake cannot make a 180 degree turn
            if (to_vec<int>(input_direction.value()) != -1 * to_vec<int>(curr_direction_)) {
                next_direction_ = input_direction.value();
            }
        }
    }
}

bool level::is_dead() {
    return is_dead_;
}

void level::restart() {
    snake_.pop_tail();
    is_dead_ = false;
}

std::size_t level::score() const {
    return snake_.length() - 1zu; 
}

void level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(grid_, states);
}

void level::spawn_apple() {
    std::random_device dev{};
    std::mt19937 rng{dev()};
    std::uniform_int_distribution row_dist{0zu, level::rows - 1zu};
    std::uniform_int_distribution column_dist{0zu, level::columns - 1zu};

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

void level::die() {
    is_dead_ = true;
}

}

