//
// Created by Марсель on 19.08.2025.
//

#include "PositionManager.h"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "UIManger/TextureManager/TextureManager.h"

#include <utility>

#include "UIManger/ElementsTypes/Constant.h"
#include "element/handler/Tracker.h"

sf::Vector2f PositionManager::get_background_position() noexcept {
    return {0.f, 0.f};
}

sf::Vector2f PositionManager::get_set_game_mode_position(elements::GameMode mode) noexcept {
    return {
        (elements::coord::MODE_BUTTON_START_X +
            (static_cast<float>(mode) *
                (static_cast<float>(elements::coord::MODE_BUTTON_END_X
                    - elements::coord::MODE_BUTTON_START_X) / elements::MODE_COUNT))),
        static_cast<float>(elements::coord::Y) / 2.f};
}

sf::Vector2f PositionManager::get_change_page_button_position() noexcept {
    return {static_cast<float>(elements::coord::CHANGE_PAGE_BUTTON_X) ,
        static_cast<float>(elements::coord::CHANGE_PAGE_BUTTON_Y)};
}

sf::Vector2f PositionManager::get_count_player_button_position(const elements::PlayerCount type) noexcept {
    switch (type) {
        case elements::PlayerCount::SINGLE: {
            return {
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_INDENT),
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_Y)
            };
        }
        case elements::PlayerCount::ONE_VS_ONE: {
            return {
                static_cast<float>(elements::coord::X -
                                   elements::coord::PLAYER_COUNT_BUTTON_INDENT -
                                   elements::coord::PLAYER_COUNT_BUTTON_SIZE_X),
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_Y)
            };
        }
    }
    std::unreachable();
}

sf::Vector2f PositionManager::get_slider_position(const elements::SlidersType type) noexcept {
    switch (type) {
        case elements::SlidersType::DiceCountSlider : {
            return {elements::coord::SLIDER_DICE_COUNT_X, elements::coord::SLIDER_DICE_COUNT_Y};
        }
    }
    std::unreachable();
}

sf::Vector2f PositionManager::get_track_lowest_value_position(elements::SlidersType type, std::size_t cells_count) noexcept {
    switch (type) {
        case elements::SlidersType::DiceCountSlider : {
            return {elements::coord::SLIDER_DICE_COUNT_X +
                (TextureManager::get_slider_texture_size(type) / (1 + cells_count) / 2.f)
                - (elements::coord::TRACK_SIZE / 2),
            elements::coord::SLIDER_DICE_COUNT_Y +
                (elements::coord::SLIDER_WIGHT / 2)  - (elements::coord::TRACK_SIZE / 2)};
        }
    }
    std::unreachable();
}




