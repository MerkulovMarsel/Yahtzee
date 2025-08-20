//
// Created by Марсель on 21.08.2025.
//

#ifndef SETPLAYERCOUNTBUTTON_H
#define SETPLAYERCOUNTBUTTON_H
#include "element/base/DynamicTouchable/DynamicTouchableElement.h"
#include "element/handler/Tracker.h"
#include "UIManger/ElementsTypes/ElementsTypes.h"

namespace elements {
    template<PlayerCount count>
    class SetPlayerCountButton final : public DynamicTouchableElement<Page::CONFIG_SETTINGS, std::size_t>, UITracker {
    public:
        explicit SetPlayerCountButton(UIManager& manager) :
        DynamicTouchableElement(
            manager.game_config.game_state.players_count,
            *manager.texture_manager.get_player_count_button_texture(count),
            PositionManager::get_count_player_button_position(count),
            [] (std::size_t& current_count, MousePos)
            {current_count = static_cast<std::size_t>(count); },
            [](sf::Sprite& sprite, const std::size_t& current_count, bool) {
                if (current_count == static_cast<std::size_t>(count)) {
                    sprite.setColor(TOUCH_COLOR);
                } else {
                    sprite.setColor(NORMAL_COLOR);
                }
            }),
        UITracker(manager){}
    };

    using SinglePlayerButton = SetPlayerCountButton<PlayerCount::SINGLE>;
    using OneVsOnePlayerButton = SetPlayerCountButton<PlayerCount::ONE_VS_ONE>;
}

#endif //SETPLAYERCOUNTBUTTON_H
