#include "direction.h"
#include <cstdlib>
#include <print>
#include <SFML/Graphics.hpp>
#include <game.h>

void handle_event(sf::Window& window, sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
}

int main() try {
    sf::RenderWindow window{sf::VideoMode{800, 600}, "snake"};

    // number of ticks per second
    constexpr float tick_rate{2.0f};
    sf::Clock clock{};
    snake::game game{};
    
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            handle_event(window, event);
            game.handle_event(event);
        }

        window.clear(sf::Color::Black);

        if (clock.getElapsedTime().asSeconds() > (1.0f / tick_rate)) {
            game.tick();
            clock.restart();
        }

        window.draw(game);
        window.display();
    }
}
catch (const std::exception& e) {
    std::println(stderr, "{}", e.what());
    return EXIT_FAILURE;
}
catch (...) {
    std::println(stderr, "an unknown error occurred");
    return EXIT_FAILURE;
}

