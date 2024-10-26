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
    sf::VideoMode video_mode{snake::game::width, snake::game::height};
    sf::RenderWindow window{video_mode, "snake"};

    // prevent SFML from writing errors to the terminal 
    sf::err().rdbuf(nullptr);

    // number of ticks per second
    constexpr float tick_rate{4.0f};
    sf::Clock clock{};

    sf::Vector2f top_left{};
    snake::game game{top_left};
    
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

