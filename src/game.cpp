#include <game.h>
#include <optional>

namespace snake {

game::game(keymap keymap)
    :keymap_{keymap} {
    snake_.draw(grid_);
}

void game::tick() {
    snake_.move(direction_);

    // cannot put draw logic in `game::draw` since it's marked as const
    grid_.clear();
    snake_.draw(grid_);
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

}

