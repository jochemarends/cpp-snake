#ifndef GRID_H
#define GRID_H

#include <cstddef>
#include <map>
#include <stdexcept>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace snake {

template<std::size_t Rows, std::size_t Columns>
struct grid : sf::Drawable {
    static constexpr std::size_t line_width{20};

    grid(sf::Vector2f top_left, std::size_t tile_size);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * Fill tile with a color.
     *
     * @param index Row-major index of the tile to fill.
     * @param color Color to fill tile with.
     */
    void fill(sf::Vector2<std::size_t> index, sf::Color color);

    /**
     * Clear the grid.
     */
    void clear();

    sf::Vector2f top_left() const;

    /**
     * Obtain grid size in pixels.
     *
     * @return Grid size in pixels.
     */
    sf::Vector2<std::size_t> size() const;

    /**
     * Obtain tile size in pixels.
     *
     * @return Tile size in pixels.
     */
    std::size_t tile_size() const;

    /**
     * Obtain the dimensions of the grid.
     *
     * @return A two-component vector where the first and second component equal the amount of rows and columns of the grid respectively.
     */
    sf::Vector2<std::size_t> dims() const;
private:
    struct cmp {
        bool operator()(sf::Vector2<std::size_t> a, sf::Vector2<std::size_t> b) const {
            return std::tie(a.x, a.y) < std::tie(b.x, b.y);
        }
    };

    /**
     * Consider using a hash table, however, SFML's vector is not hashable.
     */
    std::map<sf::Vector2<std::size_t>, sf::Color, cmp> tiles_{};
    sf::Vector2f top_left_{};
    std::size_t tile_size_{};
};

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tile{sf::Vector2f{static_cast<float>(tile_size_), static_cast<float>(tile_size_)}};

    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(-(grid::line_width / 2.0f));
    
    for (auto [index, color] : tiles_) {
        sf::Vector2f pos{top_left_};

        // using row-major indices!
        pos.y += static_cast<float>(index.x * tile_size_);
        pos.x += static_cast<float>(index.y * tile_size_);

        tile.setPosition(pos.x, pos.y);
        tile.setFillColor(color);
        target.draw(tile, states);
    }
}

template<std::size_t Rows, std::size_t Columns>
grid<Rows, Columns>::grid(sf::Vector2f top_left, std::size_t tile_size)
    :top_left_{top_left}, tile_size_{tile_size} {}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::fill(sf::Vector2<std::size_t> index, sf::Color color) {
    if (index.x >= Rows || index.x < 0 || index.y >= Columns || index.y < 0) {
        throw std::out_of_range{"attempt to fill an out of range tile"};
    }
    tiles_[index] = color;
}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::clear() {
    tiles_.clear();
}

template<std::size_t Rows, std::size_t Columns>
sf::Vector2f grid<Rows, Columns>::top_left() const {
    return top_left_;
}

template<std::size_t rows, std::size_t columns>
sf::Vector2<std::size_t> grid<rows, columns>::size() const {
    return tile_size_ * dims();
}

template<std::size_t Rows, std::size_t Columns>
std::size_t grid<Rows, Columns>::tile_size() const {
    return tile_size_;
}

template<std::size_t Rows, std::size_t Columns>
sf::Vector2<std::size_t> grid<Rows, Columns>::dims() const {
    return sf::Vector2{Rows, Columns};
}

}

#endif

