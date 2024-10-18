#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <map>
#include <cstddef>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <stdexcept>

namespace snake {

struct cmp {
    bool operator()(sf::Vector2u a, sf::Vector2u b) const {
        return std::tie(a.x, a.y) < std::tie(b.x, b.y);
    }
};

template<std::size_t Rows, std::size_t Columns>
struct grid : sf::Drawable {
    grid(sf::Vector2f top_left, std::size_t tile_size);

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
     * Fill tile with a color.
     *
     * @param index Row-major index of the tile to fill.
     * @param color Color to fill tile with.
     */
    void fill(sf::Vector2u index, sf::Color color);
    
    /**
     * Clear the grid.
     */
    void clear();

    sf::Vector2u top_left() const;

    /**
     * Obtain grid size in pixels.
     *
     * @return Grid size in pixels.
     */
    sf::Vector2u size() const;

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
    sf::Vector2u dims() const;
private:
    /**
     * Consider using a hash table, however, SFML's vector is not hashable.
     */
    std::map<sf::Vector2u, sf::Color, cmp> tiles_{};
    sf::Vector2u top_left_{};
    std::size_t tile_size_{};
};


template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tile{sf::Vector2f{static_cast<float>(tile_size_), static_cast<float>(tile_size_)}};
    
    for (auto [index, color] : tiles_) {
        auto offset = top_left_ + static_cast<unsigned>(tile_size_) * index;

        // using row-major indices!
        tile.setPosition(offset.y, offset.x);
        tile.setFillColor(color);

        target.draw(tile, states);
    }
}

template<std::size_t Rows, std::size_t Columns>
grid<Rows, Columns>::grid(sf::Vector2f top_left, std::size_t tile_size)
    :top_left_{top_left}, tile_size_{tile_size} {}


template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::fill(sf::Vector2u index, sf::Color color) {
    if (index.x >= Rows || index.y >= Columns) {
        throw std::out_of_range{"attempt to fill an out of range tile"};
    }
    tiles_[index] = color;
}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::clear() {
    tiles_.clear();
}

template<std::size_t Rows, std::size_t Columns>
sf::Vector2u grid<Rows, Columns>::top_left() const {
    return top_left_;
}

template<std::size_t rows, std::size_t columns>
sf::Vector2u grid<rows, columns>::size() const {
    return tile_size_ * dims();
}

template<std::size_t Rows, std::size_t Columns>
std::size_t grid<Rows, Columns>::tile_size() const {
    return tile_size_;
}

template<std::size_t Rows, std::size_t Columns>
sf::Vector2u grid<Rows, Columns>::dims() const {
    return sf::Vector2u{Rows, Columns};
}

}

#endif

