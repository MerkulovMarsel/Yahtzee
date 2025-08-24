//
// Created by Марсель on 21.08.2025.
//

#ifndef SETPLAYERCOUNTBUTTON_H
#define SETPLAYERCOUNTBUTTON_H
#include "UIManger/UIManager.h"
#include "element/base/DynamicTouchable/DynamicTouchableElement.h"
#include "element/handler/Tracker.h"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include <SFML/Graphics/Sprite.hpp>
#include <cstddef>

namespace elements {
    template<PlayerCountButtonType count>
    class SetPlayerCountButton final : public DynamicTouchableElement<Page::CONFIG_SETTINGS, std::size_t>, UITracker {

    public:
        explicit SetPlayerCountButton(UIManager& manager) :
        DynamicTouchableElement(
            manager.game_config.game_state.players_count,
            *manager.texture_manager.get_player_count_button_texture(),
            manager.get_position(count),
            [&] (std::size_t& current_count, MousePos)
            {current_count = manager.data.get_info<PlayerCountButtonType, PlayerCountInfo, PlayerCountData>(count)->player_count; },
            [&](sf::Sprite& sprite, const std::size_t& current_count, bool) {
                if (current_count == manager.data.get_info<PlayerCountButtonType, PlayerCountInfo, PlayerCountData>(count)->player_count) {
                    sprite.setColor(TOUCH_COLOR);
                } else {
                    sprite.setColor(NORMAL_COLOR);
                }
            }),
        UITracker(manager) {
            this->set_origin_to_centre();
            manager.texture_manager.draw_text(
                this->get_sprite(),
                manager.data.get_info<PlayerCountButtonType, PlayerCountInfo, PlayerCountData>(count)->text,
                static_cast<unsigned int>(manager.data.get_info<PlayerCountButtonType, PlayerCountInfo, PlayerCountData>(count)->char_size));
        }
    };

    using SinglePlayerButton = SetPlayerCountButton<PlayerCountButtonType::Single>;
    using OneVsOnePlayerButton = SetPlayerCountButton<PlayerCountButtonType::OneVsOne>;
}

#endif //SETPLAYERCOUNTBUTTON_H
