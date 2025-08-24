//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "ElementsTypes/Data.h"
#include "ElementsTypes/ElementsTypes.h"
#include "GameConfig/GameConfig.h"
#include "PositionManger/PositionManager.h"
#include "TextureManager/TextureManager.h"
#include <cstddef>
#include <optional>


struct UIManager {
    TextureManager texture_manager;
    elements::Data data;
    PositionManager position_manager;
    GameConfig game_config;
    elements::Page current_page = elements::Page::START_SETTING;
    std::optional<elements::GameMode> mode;
    mutable std::size_t elements_count = 0;

    explicit UIManager(const char* argv0): texture_manager(argv0) {
    }

    template <elements::ElementType Type>
    elements::Cord get_position(Type type) const {
        return position_manager.get_position(data, type);
    }

    std::size_t& get_slider_state(elements::SlidersType slider);

    static std::size_t get_slider_lowest_value(elements::SlidersType slider);

    void add() const {
        elements_count++;
    }
};


#endif //CONFIG_H
