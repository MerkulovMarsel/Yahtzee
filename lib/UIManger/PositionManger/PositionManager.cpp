//
// Created by Марсель on 19.08.2025.
//

#include "PositionManager.h"
#include "UIManger/ElementsTypes/Data.h"
#include "UIManger/ElementsTypes/ElementsTypes.h"

#include <utility>
#include <vector>

#include "UIManger/ElementsTypes/Constant.h"

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

std::vector<float> PositionManager::get_slider_border_positions(
    const elements::SliderInfo &slider_info,
    const float slider_size) noexcept {
    const auto cells_count = (slider_info.value_max - slider_info.value_min + 1U);
    const auto cells_size = slider_size / static_cast<float>(cells_count);
    std::vector<float> positions;
    positions.reserve(cells_count - 1);
    for (auto value = slider_info.value_min; value < slider_info.value_max; value++) {
        positions.emplace_back(cells_size * (static_cast<float>(value) - static_cast<float>(slider_info.value_min) + 1U));
    }
    return positions;
}


