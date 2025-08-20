//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "ElementsTypes/ElementsTypes.h"
#include "GameConfig/GameConfig.h"
#include "PositionManger/PositionManager.h"
#include "TextureManager/TextureManager.h"


struct UIManager {
    TextureManager texture_manager;
    PositionManager position_manager;
    GameConfig game_config;
    Page current_page = Page::START_SETTING;
    mutable std::size_t elements_count = 0;

    explicit UIManager(const char* argv0): texture_manager(argv0) {
    }


    std::size_t& get_slider_state(SlidersType slider);

    static std::size_t get_slider_lowest_value(SlidersType slider);

    void add() const {
        elements_count++;
    }
};


#endif //CONFIG_H
