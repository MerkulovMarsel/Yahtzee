//
// Created by Марсель on 19.08.2025.
//

#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H


#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "SFML/System/Vector2.hpp"
#include "UIManger/ElementsTypes/Constant.h"
#include "UIManger/ElementsTypes/Data.h"
#include <cstdint>
#include <vector>


struct PositionManager {

    sf::Vector2f get_dice_position(std::size_t dice_index) const noexcept;
    sf::Vector2f get_category_position(std::size_t category_index) const noexcept;
    sf::Vector2f get_play_button_position() const noexcept;
    sf::Vector2f get_roll_button_position() const noexcept;


    static sf::Vector2f get_mode_position(std::size_t mode_index) noexcept;
    static sf::Vector2f get_background_position() noexcept;
    static sf::Vector2f get_set_game_mode_position(elements::GameMode mode) noexcept;
    static sf::Vector2f get_change_page_button_position() noexcept;
    static sf::Vector2f get_count_player_button_position(elements::PlayerCount type) noexcept;
    static sf::Vector2f get_slider_position(elements::SlidersType type) noexcept;
    static std::vector<float> get_slider_border_positions(const elements::SliderInfo &slider_info, float slider_size) noexcept;


    template <elements::ElementType Type>
    sf::Vector2f get_position(
        const elements::Data& data,
        Type type,
        const sf::Vector2f screen_size = {elements::coord::X, elements::coord::Y},
        const sf::Vector2f pos_start = {0.f, 0.f}) const {
        const auto raw_position = data.get_position(type);
        if (std::holds_alternative<elements::PositionType>(raw_position)) {
            const auto pos_type = std::get<elements::PositionType>(raw_position);
            std::size_t x = static_cast<std::uint8_t>(pos_type) % 4U;
            std::size_t y = static_cast<std::uint8_t>(pos_type) / 4U;
            return elements::Cord{screen_size.x / 4.f * x, screen_size.y / 4.f * y} + pos_start;
        }
        if (std::holds_alternative<elements::HighFix>(raw_position)) {
            const auto [type, pos] = std::get<elements::HighFix>(raw_position);
            switch (type) {
                case elements::PositionType::LEFT :
                case elements::PositionType::DOWN_LEFT :
                case elements::PositionType::UP_LEFT : {
                    return elements::Cord{pos_start.x + (screen_size.x / 4.f),pos + pos_start.y};
                }
                case elements::PositionType::RIGHT :
                case elements::PositionType::UP_RIGHT :
                case elements::PositionType::DOWN_RIGHT: {
                    return elements::Cord{pos_start.x + ((screen_size.x / 4.f) * 3.f),pos + pos_start.y};
                }
                default: {
                    return elements::Cord{pos_start.x + (screen_size.x / 2.f),pos + pos_start.y};
                }
            }
        }
        return std::get<elements::Cord>(raw_position) + pos_start;
    }
};


#endif //POSITIONMANAGER_H
