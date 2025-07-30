//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <cstdint>

#include "GameConfig/GameConfig.h"


struct Config {
    enum class Phase : uint8_t {
        START_SETTING,
        GAME_PLAYING,
        GAME_OVER
    };




    static constexpr std::size_t GAME_OBJECT_COUNT = 20;

    Phase phase = Phase::START_SETTING;
    GameConfig game_config;
};



#endif //CONFIG_H
