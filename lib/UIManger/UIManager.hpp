//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#include "ElementsTypes/Data.hpp"
#include "ElementsTypes/ElementsTypes.hpp"
#include "GameConfig/GameConfig.hpp"
#include "PositionManger/PositionManager.hpp"
#include "TextureManager/TextureManager.hpp"
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

    void add() const {
        elements_count++;
    }

    template <elements::ElementType Type, Type type>
    requires elements::has_state<Type, type>
    [[nodiscard]] typename elements::Info<Type, type>::State* get_state() {
        if constexpr (std::is_same_v<Type, elements::SlidersType>) {
            if constexpr(type == elements::SlidersType::DiceCountSlider) {
                return &game_config.game_state.dice_count;
            }
        }
        if constexpr (std::is_same_v<Type, elements::ScreenType>) {
            if constexpr (type == elements::ScreenType::RollCountScreen) {
                return &game_config.game_state.roll_count;
            }
        }
        return nullptr;
    }


};


#endif //CONFIG_H
