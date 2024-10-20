#ifndef GAME_H
#define GAME_H

#include <SFML/Window/Event.hpp>
#include <snake.h>
#include <direction.h>
#include <grid.h>
#include <keymap.h>

namespace snake {

struct game : sf::Drawable {
    game(keymap keymap = vi_keymap);

    /**
     * Handler the game's logic.
     */
    void tick();
    
    void handle_event(const sf::Event& e);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    // grid constants
    static constexpr std::size_t tile_size_{100zu};
    static constexpr std::size_t rows_{5zu};
    static constexpr std::size_t columns_{5zu};

    // snake constants
    static inline const sf::Vector2 start_pos_{0, 0};

    keymap keymap_{};
    grid<rows_, columns_> grid_{{}, tile_size_};
    snake snake_{start_pos_};
    direction direction_{direction::left};
};

}

#endif

