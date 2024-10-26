#ifndef LEVEL_H
#define LEVEL_H

#include <cstddef>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <apple.h>
#include <direction.h>
#include <grid.h>
#include <keymap.h>
#include <snake.h>

namespace snake {

/**
 * Manages gameplay.
 */
struct level : sf::Drawable {
    level(sf::Vector2f top_left);

    void tick();

    void draw();

    void handle_collisions();

    void handle_event(const sf::Event& e, const keymap& keymap = vi_keymap);

    /**
     * Check whether the level is played.
     */
    bool is_dead() const;

    void restart();

    std::size_t score() const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static constexpr std::size_t tile_size{40zu};
    static constexpr std::size_t rows{10zu};
    static constexpr std::size_t columns{10zu};

    static constexpr std::size_t width{columns * tile_size};
    static constexpr std::size_t height{rows * tile_size};

    static inline const sf::Vector2i start_pos{width, height};
    static inline const direction start_dir{direction::right};
private:
    /**
     * Spawn apple on a random and unoccupied tile of the grid.
     */
    void spawn_apple();

    /**
     * Stop the game.
     */
    void die();

    bool is_dead_{true};
    direction curr_direction_{start_dir};
    direction next_direction_{curr_direction_};

    grid<rows, columns> grid_;
    struct snake snake_{start_pos};
    std::vector<apple> apples_{};
};

}

#endif

