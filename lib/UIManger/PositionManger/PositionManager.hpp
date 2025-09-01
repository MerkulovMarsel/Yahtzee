//
// Created by Марсель on 19.08.2025.
//

#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H


#include "UIManger/ElementsTypes/ElementsTypes.hpp"
#include "SFML/System/Vector2.hpp"
#include "UIManger/ElementsTypes/Constant.hpp"
#include "UIManger/ElementsTypes/Data.hpp"
#include <vector>



namespace sf {
    inline Vector2f operator*(const Vector2f& a, const Vector2f& b) {
        return {a.x * b.x, a.y * b.y};
    }
}

struct PositionManager {
    static sf::Vector2f get_background_position() noexcept;
    static sf::Vector2f get_set_game_mode_position(elements::GameMode mode) noexcept;
    static sf::Vector2f get_change_page_button_position() noexcept;

    static sf::Vector2f get_slider_position(elements::SlidersType type) noexcept;
    static std::vector<float> get_slider_border_positions(const elements::SliderInfo &slider_info, float slider_size) noexcept;
    static std::vector<float> get_slider_value_positions(const elements::SliderInfo &slider_info, float slider_size) noexcept;


    template <elements::ElementType Type>
    sf::Vector2f get_position(
        const elements::Data& data,
        Type type,
        const sf::Vector2f screen_size = {elements::coord::X, elements::coord::Y},
        const sf::Vector2f pos_start = {0.f, 0.f}) const {
        const auto position = data.get_position(type);
        if (std::holds_alternative<elements::PositionType>(position)) {
            const auto pos_type = std::get<elements::PositionType>(position);
            return (screen_size * elements::get_normalized_coord(pos_type)) + pos_start;
        }
        if (std::holds_alternative<elements::HighFix>(position)) {
            const auto [type, pos] = std::get<elements::HighFix>(position);
            return elements::Cord{screen_size.x * elements::get_normalized_coord(type).x, screen_size.y} + pos_start;
        }
        return std::get<elements::Cord>(position) + pos_start;
    }

    [[nodiscard]] static sf::Vector2f get_position(
        const elements::Position &position,
        sf::Vector2f screen_size = {elements::coord::X, elements::coord::Y},
        sf::Vector2f pos_start = {0.f, 0.f});
};


#endif //POSITIONMANAGER_H
