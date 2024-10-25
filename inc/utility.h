#ifndef UTILITY_H
#define UTILITY_H

#include <format>
#include <utility>
#include <SFML/System/Vector2.hpp>

template<typename T>
struct std::formatter<sf::Vector2<T>> : std::formatter<string_view> {
    auto format(sf::Vector2<T> vec, std::format_context& ctx) const {
        std::string str{};
        std::format_to(std::back_inserter(str), "({}, {})", vec.x, vec.y);
        return std::formatter<string_view>::format(str, ctx);
    }
};

namespace snake {

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<arithmetic T>
constexpr T wrap(T v, T lo, T hi) {
    if (v < lo) {
        return wrap(hi - (lo - v - static_cast<T>(1)), lo, hi);
    }
    else if (v > hi) {
        return wrap(lo + v - hi - static_cast<T>(1), lo, hi);
    }
    return v;
}

constexpr bool between(arithmetic auto v, arithmetic auto lo, arithmetic auto hi) {
    return std::cmp_greater_equal(v, lo) && std::cmp_less_equal(v, hi);
}

enum class layout {
    row_major,
    column_major,
};

}

#endif

