//
// Created by Марсель on 21.08.2025.
//

#ifndef SETPLAYERCOUNTBUTTON_H
#define SETPLAYERCOUNTBUTTON_H
#include "UIManger/ElementsTypes/Data.h"
#include "UIManger/UIManager.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include <SFML/Graphics/Sprite.hpp>
#include <cstddef>

#include "elements/base/general/DynamicTouchable/DynamicTouchableElement.hpp"

#define GET_INFO manager.data.get_info<PlayerCountButtonType, PlayerCountInfo, PlayerCountData>(count)

namespace elements {
    template<PlayerCountButtonType count>
    class SetPlayerCountButton final :  public PageElement<Page::CONFIG_SETTINGS>,
                                        public DynamicTouchableElement<std::size_t>,
                                        public UITracker {

    public:
        explicit SetPlayerCountButton(UIManager& manager) :
        DynamicTouchableElement(
            manager.game_config.game_state.players_count,

            { .texture = manager.texture_manager.get_player_count_button_texture(),
            .position = manager.get_position(count)},

            [&](sf::Sprite &sprite, const std::size_t &current_count) {
                if (current_count == GET_INFO->player_count) {
                    sprite.setColor(TOUCH_COLOR);
                } else {
                    sprite.setColor(NORMAL_COLOR);
                }
            },

            { .touch_callback = [&] (std::size_t& current_state, MousePos) {
                current_state = GET_INFO->player_count;
            }}),
            UITracker(manager){
            this->set_origin_to_centre();

            manager.texture_manager.draw_text(
                this->get_sprite(),
                GET_INFO->text,
                static_cast<unsigned int>(GET_INFO->char_size));}
    };

    using SinglePlayerButton = SetPlayerCountButton<PlayerCountButtonType::Single>;
    using OneVsOnePlayerButton = SetPlayerCountButton<PlayerCountButtonType::OneVsOne>;
}

#undef GET_INFO

#endif //SETPLAYERCOUNTBUTTON_H
