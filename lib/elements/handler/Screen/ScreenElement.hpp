//
// Created by Марсель on 24.08.2025.
//

#ifndef STATESCREENELEMENT_H
#define STATESCREENELEMENT_H

#include "UIManger/ElementsTypes/Constant.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.hpp"
#include "UIManger/GameConfig/GameConfig.hpp"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "elements/base/general/DynamicUntouchable/DynamicUntouchableElement.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"
#include "UIManger/ElementsTypes/Data.hpp"
#include "UIManger/UIManager.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>
#include <concepts>
#include <string>
#include <type_traits>


template<>
struct elements::Info<elements::ScreenType, elements::ScreenType::RollCountScreen> {
    using State = GameConfig::GameState::RollCountType;
    static constexpr auto page = Page::CONFIG_SETTINGS;
    static constexpr auto char_size = CharSizeType::M;
    static sf::String state_to_string(const State& state) {
        if (state.first) {
            return std::to_string(state.first.value());
        }
        return L"\u221E";
    }
    static constexpr Position get_position() {
        return HighFix{PositionType::MID, coord::ROLL_COUNT_SCREEN_Y};
    }
};

namespace elements {
    template<ScreenType type>
    concept screen_type_trait =
                initilized_type<ScreenType, type> &&
                has_position<ScreenType, type> &&
                has_state<ScreenType, type> &&
                std::is_same_v<std::remove_cv_t<decltype(Info<ScreenType, type>::char_size)>, CharSizeType> &&
                    requires(typename Info<ScreenType, type>::State state) {
                    { Info<ScreenType, type>::state_to_string(state) } -> std::convertible_to<sf::String>;};



    template <ScreenType type>
    requires screen_type_trait<type>
    class ScreenElement final : public PageElement<Info<ScreenType, type>::page>,
                                public DynamicUntouchableElement<typename Info<ScreenType, type>::State>,
                                public UITracker{
        using Info = Info<ScreenType, type>;

    public:
        explicit ScreenElement(UIManager& manager) :
        DynamicUntouchableElement<typename Info::State>(
           *manager.get_state<ScreenType, type>(),
           { .texture = manager.texture_manager.get_square_setting_texture(),
           .position = PositionManager::get_position(Info::get_position())},

           [&](sf::Sprite& sprite, const typename Info::State& state) {
                manager.texture_manager.draw_text(
                    sprite,
                    Info::state_to_string(state),
                    static_cast<unsigned int>(Info::char_size));
           }
        ), UITracker(manager) {
            this->set_origin_to_centre();
        }
    };

    using RollCountScreenElement = ScreenElement<ScreenType::RollCountScreen>;

}

#endif //STATESCREENELEMENT_H
