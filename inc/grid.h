#ifndef GRID_H
#define GRID_H

#include <cstddef>
#include <ranges>
#include <stdexcept>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace snake {

template<std::size_t Rows, std::size_t Columns>
struct grid : sf::Drawable {
    static constexpr std::size_t line_width{10};

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

    template<typename Self>
    auto&& tiles(this Self&& self, std::size_t row, std::size_t column);

    template<typename Self>
    auto&& operator[](this Self&& self, std::size_t row, std::size_t column);
private:
    auto indices() const;

    /**
     * Consider using a hash table, however, SFML's vector is not hashable.
     */
    std::array<sf::Color, Rows * Columns> tiles_{};
    sf::Vector2f top_left_{};
    std::size_t tile_size_{};
};

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::RectangleShape tile{sf::Vector2f{static_cast<float>(tile_size_), static_cast<float>(tile_size_)}};

    tile.setOutlineColor(sf::Color::Black);
    tile.setOutlineThickness(-(grid::line_width / 2.0f));
    
    for (auto [row, column] : indices()) {
        sf::Vector2f pos{top_left_};

        // using row-major indices!
        pos.y += static_cast<float>(row * tile_size_);
        pos.x += static_cast<float>(column * tile_size_);

        sf::Color color{operator[](row, column)};
        tile.setPosition(pos.x, pos.y);
        tile.setFillColor(color);
        target.draw(tile, states);
    }
}

template<std::size_t Rows, std::size_t Columns>
grid<Rows, Columns>::grid(sf::Vector2f top_left, std::size_t tile_size)
    :top_left_{top_left}, tile_size_{tile_size} {
    clear();
}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::fill(sf::Vector2<std::size_t> index, sf::Color color) {
    operator[](index.x, index.y) = color;
}

template<std::size_t Rows, std::size_t Columns>
void grid<Rows, Columns>::clear() {
    std::ranges::fill(tiles_, sf::Color::Transparent);
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

template<std::size_t Rows, std::size_t Columns>
template<typename Self>
auto&& grid<Rows, Columns>::tiles(this Self&& self, std::size_t row, std::size_t column) {
    return self.tiles_[row * Columns + column];
}

template<std::size_t Rows, std::size_t Columns>
template<typename Self>
auto&& grid<Rows, Columns>::operator[](this Self&& self, std::size_t row, std::size_t column) {
    if (row >= Rows || column >= Columns) {
        throw std::out_of_range{"attempt to fill an out of range tile"};
    }
    return self.tiles_[row * Columns + column];
}

template<std::size_t Rows, std::size_t Columns>
auto grid<Rows, Columns>::indices() const {
    auto row_indices = std::views::iota(0zu, Rows);
    auto column_indices = std::views::iota(0zu, Columns);
    return std::views::cartesian_product(row_indices, column_indices);
}

}

#endif

