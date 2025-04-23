#include <game.h>
#include <format>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

namespace snake {

game::game(sf::Vector2f top_left)
    :level_{sf::Vector2f{top_left.x, top_left.y + top_bar_height}} {
    
    // load font
    if (!font_.openFromFile(game::font_file_path)) {
        throw std::runtime_error{std::format("failed to load font from \"{}\"", game::font_file_path)};
    }

    // configure score text
    score_text_.setFont(font_);
    score_text_.setCharacterSize(game::top_bar_height * 0.8);
    score_text_.setFillColor(sf::Color::White);

    // configure start prompt text
    start_text_.setFont(font_);
    start_text_.setFillColor(sf::Color::White);
    start_text_.setString("press any key to start");
    // center text
    start_text_.setOrigin(start_text_.getGlobalBounds().position / 2.0f + start_text_.getLocalBounds().getCenter());
    start_text_.setPosition({game::width / 2.0, game::height / 2.0});
    start_text_.setScale({0.75, 0.75});

    update_top_bar();
}

void game::tick() {
    level_.tick();
    update_top_bar();
}

void game::update_top_bar() {
    // keep old score until a new attempt starts
    if (!level_.is_dead() || score_text_.getString().isEmpty()) {
        score_text_.setString(std::format("{}", level_.score()));
    }
}

void game::handle_event(const sf::Event& e) {
    if (e.is<sf::Event::KeyPressed>() && level_.is_dead()) {
        level_.restart();
    }
    
    level_.handle_event(e, keymap_);
}

void game::draw_border(sf::RenderTarget& target, sf::RenderStates states) const {
    constexpr float border_width{-2.0f};
    const sf::Color border_color{sf::Color::White};

    // draw a border around the level
    sf::RectangleShape border{sf::Vector2f{level::width, level::height}};
    border.move({0, game::top_bar_height});
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(border_color);
    border.setOutlineThickness(border_width);

    target.draw(border, states);
}

void game::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(level_, states);
    draw_border(target, states);
    target.draw(score_text_, states);

    if (level_.is_dead()) {
        target.draw(start_text_, states);
    }
}

}

