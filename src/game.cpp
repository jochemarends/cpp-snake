#include <game.h>
#include <format>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace snake {

game::game(sf::Vector2f top_left)
    :level_{sf::Vector2f{top_left.x, top_left.y + top_bar_height}} {
    font_.loadFromFile("./libertine.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(game::top_bar_height * 0.8);
    text_.setFillColor(sf::Color::White);
    update_top_bar();
}

void game::tick() {
    level_.tick();
    update_top_bar();
}

void game::update_top_bar() {
    text_.setString(std::format("score: {}", level_.score()));
}

void game::handle_event(const sf::Event& e) {
    if (level_.is_dead()) {
        level_.restart();
    }
    
    level_.handle_event(e, keymap_);
}

void game::draw_border(sf::RenderTarget& target, sf::RenderStates states) const {
    constexpr float border_width{-2.0f};
    const sf::Color border_color{sf::Color::White};

    // draw a border around the level
    sf::RectangleShape border{sf::Vector2f{level::width, level::height}};
    border.move(0, game::top_bar_height);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(border_color);
    border.setOutlineThickness(border_width);

    target.draw(border, states);
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(level_, states);
    draw_border(target, states);
    target.draw(text_, states);
}

}

