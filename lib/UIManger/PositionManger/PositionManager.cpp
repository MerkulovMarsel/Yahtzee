//
// Created by Марсель on 19.08.2025.
//

#include "PositionManager.h"
#include "UIManger/TextureManager/TextureManager.h"

#include <utility>

sf::Vector2f PositionManager::get_background_position() noexcept {
    return {0.f, 0.f};
}

sf::Vector2f PositionManager::get_set_game_mode_position(GameMode mode) noexcept {
    return {
        (elements::coord::MODE_BUTTON_START_X +
            (static_cast<float>(mode) *
                (static_cast<float>(elements::coord::MODE_BUTTON_END_X
                    - elements::coord::MODE_BUTTON_START_X) / elements::MODE_COUNT))),
        static_cast<float>(elements::coord::Y)};
}

sf::Vector2f PositionManager::get_change_page_button_position() noexcept {
    return {static_cast<float>(elements::coord::CHANGE_PAGE_BUTTON_X) ,
        static_cast<float>(elements::coord::CHANGE_PAGE_BUTTON_Y)};
}

sf::Vector2f PositionManager::get_count_player_button_position(const PlayerCount type) noexcept {
    switch (type) {
        case PlayerCount::SINGLE : {
            return {static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_INDENT),
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_Y)};
        }
        case PlayerCount::ONE_VS_ONE : {
            return {static_cast<float>(elements::coord::X     -
                    elements::coord::PLAYER_COUNT_BUTTON_INDENT  -
                    elements::coord::PLAYER_COUNT_BUTTON_SIZE_X),
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_Y)};
        }
    }
    std::unreachable();
}

sf::Vector2f PositionManager::get_slider_position(const SlidersType type) noexcept {
    switch (type) {
        case SlidersType::DiceCountSlider : {
            return {elements::coord::SLIDER_DICE_COUNT_X, elements::coord::SLIDER_DICE_COUNT_Y};
        }
    }
    std::unreachable();
}

sf::Vector2f PositionManager::get_track_lowest_value_position(SlidersType type) noexcept {
    switch (type) {
        case SlidersType::DiceCountSlider : {
            return {elements::coord::SLIDER_DICE_COUNT_X +
                (TextureManager::get_slider_texture_size(type) / static_cast<std::size_t>(type) / 2.f)
                - (elements::coord::TRACK_SIZE / 2),
            elements::coord::SLIDER_DICE_COUNT_Y +
                (elements::coord::SLIDER_WIGHT / 2)  - (elements::coord::TRACK_SIZE / 2)};
        }
    }
    std::unreachable();
}


