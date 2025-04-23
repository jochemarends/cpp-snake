#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <keymap.h>
#include <level.h>

namespace snake {

struct game : sf::Drawable {
    game(sf::Vector2f top_left);

    void tick();

    void handle_event(const sf::Event& e);

    void update_top_bar();

    void draw_border(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    static constexpr std::size_t top_bar_height{60};
    static constexpr std::size_t width{level::width};
    static constexpr std::size_t height{top_bar_height + level::height};

    static inline const std::string font_file_path{"./SpaceMono-Regular.ttf"};
private:
    sf::Font font_{};
    sf::Text score_text_{font_};
    sf::Text start_text_{font_};

    std::size_t score_{};
    keymap keymap_{vi_keymap};
    level level_;
};

}

#endif

