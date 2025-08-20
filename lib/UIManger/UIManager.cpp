//
// Created by Марсель on 25.07.2025.
//

#include "UIManager.h"

#include <utility>

std::size_t& UIManager::get_slider_state(const SlidersType slider) {
    switch (slider) {
        case SlidersType::DiceCountSlider : {
            return game_config.game_state.dice_count;
        }
    }
    std::unreachable();
}

std::size_t UIManager::get_slider_lowest_value(const SlidersType slider) {
    switch (slider) {
        case SlidersType::DiceCountSlider : {
            return elements::MIN_COUNT_DICE;
        }
    }
    std::unreachable();
}
