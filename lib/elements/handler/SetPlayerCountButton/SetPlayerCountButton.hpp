//
// Created by Марсель on 21.08.2025.
//

#ifndef SETPLAYERCOUNTBUTTON_H
#define SETPLAYERCOUNTBUTTON_H

#include "UIManger/ElementsTypes/Constant.hpp"
#include "UIManger/ElementsTypes/Data.hpp"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "UIManger/UIManager.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <cstddef>
#include <type_traits>

#include "elements/base/general/DynamicTouchable/DynamicTouchableElement.hpp"

template<elements::PlayerCountButtonType type>
struct elements::Info<elements::PlayerCountButtonType, type> {
    static constexpr auto page = Page::CONFIG_SETTINGS;
    static constexpr auto player_count = (type == PlayerCountButtonType::Single) ? 1ULL : 2ULL;

    static constexpr Position get_position() {
        return HighFix{
            ((type == PlayerCountButtonType::Single) ? PositionType::LEFT : PositionType::RIGHT),
            coord::PLAYER_COUNT_BUTTON_Y};
    }

    static constexpr auto char_size = CharSizeType::S;
    static constexpr sf::String get_text() {
        if constexpr (type == PlayerCountButtonType::Single) {
            return "Single";
        }
        return "1 VS 1";
    }
};

namespace elements {
    template<PlayerCountButtonType type>
    concept player_count_button_type_trait =
                initilized_type<PlayerCountButtonType, type> &&
                has_position<PlayerCountButtonType, type> &&
                std::is_same_v<std::remove_cv_t<decltype(Info<PlayerCountButtonType, type>::char_size)>, CharSizeType> &&
                std::is_same_v<std::remove_cvref_t<decltype(Info<PlayerCountButtonType, type>::player_count)>, std::size_t>;


    template<PlayerCountButtonType count>
    requires player_count_button_type_trait<count>
    class SetPlayerCountButton final :  public PageElement<Page::CONFIG_SETTINGS>,
                                        public DynamicTouchableElement<std::size_t>,
                                        public UITracker {

        using Info = Info<PlayerCountButtonType, count>;

    public:
        explicit SetPlayerCountButton(UIManager& manager) :
        DynamicTouchableElement(
            manager.game_config.game_state.players_count,

            { .texture = manager.texture_manager.get_player_count_button_texture(),
            .position = PositionManager::get_position(Info::get_position())},

            [&](sf::Sprite &sprite, const std::size_t &current_count) {
                if (current_count == Info::player_count) {
                    sprite.setColor(TOUCH_COLOR);
                    set_scale({0.9f, 0.9f});
                } else {
                    sprite.setColor(NORMAL_COLOR);
                    set_scale({1.f, 1.f});
                }
            },

            { .touch_callback = [&] (std::size_t& current_state, MousePos) {
                current_state = Info::player_count;
            }}),
            UITracker(manager){

            this->set_origin_to_centre();

            manager.texture_manager.draw_text(
                this->get_sprite(),
                Info::get_text(),
                static_cast<unsigned int>(Info::char_size));}
    };

    using SinglePlayerButton = SetPlayerCountButton<PlayerCountButtonType::Single>;
    using OneVsOnePlayerButton = SetPlayerCountButton<PlayerCountButtonType::OneVsOne>;
}


#endif //SETPLAYERCOUNTBUTTON_H
