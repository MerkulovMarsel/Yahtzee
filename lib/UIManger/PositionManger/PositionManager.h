//
// Created by Марсель on 19.08.2025.
//

#ifndef POSITIONMANAGER_H
#define POSITIONMANAGER_H

#define CONST static constexpr auto
#include <cstddef>

#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "SFML/System/Vector2.hpp"

namespace elements::coord {
    CONST X = 1300;
    CONST Y = 900;

    CONST MODE_BUTTON_Y = 500;
    CONST MODE_BUTTON_START_X = 300;
    CONST MODE_BUTTON_END_X = X - MODE_BUTTON_START_X;

    CONST CHANGE_PAGE_BUTTON_INDENT = 30;
    CONST CHANGE_PAGE_BUTTON_X = CHANGE_PAGE_BUTTON_INDENT;
    CONST CHANGE_PAGE_BUTTON_Y = CHANGE_PAGE_BUTTON_INDENT;

    CONST CHOOSE_MODE_BUTTON_INDENT = 30;
    CONST CHOOSE_MODE_BUTTON_HEIGHT_OF_MODES = 100;

    CONST PLAYER_COUNT_BUTTON_Y = 160;
    CONST PLAYER_COUNT_BUTTON_INDENT = 240;
    CONST PLAYER_COUNT_BUTTON_SIZE_X = 186;

    CONST TRACK_SIZE = 20;
    CONST SLIDER_DICE_COUNT_X = 300;
    CONST SLIDER_DICE_COUNT_Y = 300;
    CONST SLIDER_WIGHT = 50;

}

struct PositionManager {
    sf::Vector2f get_dice_position(std::size_t dice_index) const noexcept;
    sf::Vector2f get_category_position(std::size_t category_index) const noexcept;
    sf::Vector2f get_play_button_position() const noexcept;
    sf::Vector2f get_roll_button_position() const noexcept;
    static sf::Vector2f get_mode_position(std::size_t mode_index) noexcept;
    static sf::Vector2f get_background_position() noexcept;
    static sf::Vector2f get_set_game_mode_position(GameMode mode) noexcept;
    static sf::Vector2f get_change_page_button_position() noexcept;
    static sf::Vector2f get_count_player_button_position(PlayerCount type) noexcept;
    static sf::Vector2f get_slider_position(SlidersType type) noexcept;
    static sf::Vector2f get_track_lowest_value_position(SlidersType type) noexcept;
};

#undef CONST

#endif //POSITIONMANAGER_H
