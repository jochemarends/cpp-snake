#include <cstdlib>
#include <print>
#include <SFML/Graphics.hpp>
#include <grid.h>

void handle_event(sf::Window& window, sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window.close();
    }
}

int main() try {
    sf::RenderWindow window{sf::VideoMode{800, 600}, "snake"};
    snake::grid<4, 4> grid{sf::Vector2f{0, 0}, 100};
    grid.fill({0, 0}, sf::Color::Green);
    
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            handle_event(window, event);
        }

        window.clear(sf::Color::Black);
        window.draw(grid);
        window.display();
    }
}
catch (const std::exception& e) {
    std::println(stderr, "{}", e.what());
    return EXIT_FAILURE;
}
catch (...) {
    std::println(stderr, "an unknown error occurred");
}

