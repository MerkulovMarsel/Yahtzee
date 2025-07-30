//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <array>
#include <cstdint>
#include <functional>

struct GameConfig {
    enum class DiceValues : std::uint8_t {
        UNKNOW = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6
    };
    static constexpr std::size_t DiceCount = 5;
    using Dices = std::array<DiceValues, DiceCount>;

    using ScoreType = std::size_t;
    std::size_t CategoryCount;

    struct Category {
        std::function<ScoreType(const Dices&)> calc_score;

    }
};

#endif //GAMECONFIG_H
