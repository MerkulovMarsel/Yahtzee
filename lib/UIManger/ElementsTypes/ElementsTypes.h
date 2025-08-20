//
// Created by Марсель on 19.08.2025.
//

#ifndef ELEMENTSTYPES_H
#define ELEMENTSTYPES_H
#include <cstdint>

#include "SFML/Graphics/Color.hpp"

enum class Page : std::uint8_t {
    START_SETTING   = 1,
    CONFIG_SETTINGS = 0,
    GAME_PLAYING    = 2,
    GAME_OVER       = 3
};

enum class GameMode : std::uint8_t {
    CLASSIC,
    COUNT_DOWN,
    RACE,
    SPEED,
    TEST
};

enum class PlayerCount : std::uint8_t {
    SINGLE = 1,
    ONE_VS_ONE = 2
};

enum class SlidersType : std::uint8_t {
    DiceCountSlider = 5
};

namespace elements {
    static constexpr std::size_t MODE_COUNT = 5;

    static constexpr std::size_t MAX_COUNT_DICE = 7ULL;
    static constexpr std::size_t MIN_COUNT_DICE = 3ULL;
    static constexpr std::size_t MAX_COUNT_CATEGORY = 6ULL;

    inline const sf::Color TOUCH_COLOR = sf::Color::Yellow;
    inline const sf::Color NORMAL_COLOR = sf::Color::White;
}

#endif //ELEMENTSTYPES_H
