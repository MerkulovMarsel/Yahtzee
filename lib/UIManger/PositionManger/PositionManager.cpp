//
// Created by Марсель on 19.08.2025.
//

#include "PositionManager.hpp"
#include "SFML/System/Vector2.hpp"
#include "UIManger/ElementsTypes/Data.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.hpp"

#include <utility>
#include <variant>
#include <vector>

#include "UIManger/ElementsTypes/Constant.hpp"

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
    const auto cells_count = ((slider_info.value_max - slider_info.value_min) / slider_info.value_step) + 1U;
    const auto cells_size = slider_size / static_cast<float>(cells_count);
    std::vector<float> positions;
    positions.reserve(cells_count - 1);
    for (auto value = slider_info.value_min; value < slider_info.value_max; value+= slider_info.value_step) {
        positions.emplace_back(cells_size *
            ((static_cast<float>(value) - static_cast<float>(slider_info.value_min)) / slider_info.value_step + 1U));
    }
    return positions;
}

std::vector<float> PositionManager::get_slider_value_positions(const elements::SliderInfo &slider_info,
    float slider_size) noexcept {
    const auto cells_count = ((slider_info.value_max - slider_info.value_min) / slider_info.value_step) + 1U;
    const auto cells_size = slider_size / static_cast<float>(cells_count);
    std::vector<float> positions;
    positions.reserve(cells_count);
    for (auto value = slider_info.value_min; value <= slider_info.value_max; value+= slider_info.value_step) {
        positions.emplace_back(cells_size *
            ((static_cast<float>(value) - static_cast<float>(slider_info.value_min)) / slider_info.value_step + 0.5f));
    }
    return positions;
}

sf::Vector2f PositionManager::get_position(
    const elements::Position& position,
    const sf::Vector2f screen_size,
    const sf::Vector2f pos_start) {
    if (std::holds_alternative<elements::PositionType>(position)) {
        const auto pos_type = std::get<elements::PositionType>(position);
        return screen_size * elements::get_normalized_coord(pos_type) + pos_start;
    }
    if (std::holds_alternative<elements::HighFix>(position)) {
        const auto [type, pos] = std::get<elements::HighFix>(position);
        return elements::Cord{screen_size.x * elements::get_normalized_coord(type).x, pos} + pos_start;
    }
    return std::get<elements::Cord>(position) + pos_start;
}


