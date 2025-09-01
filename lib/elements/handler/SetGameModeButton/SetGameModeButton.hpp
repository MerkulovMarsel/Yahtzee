//
// Created by Марсель on 21.08.2025.
//

#ifndef SETGAMEMODEBUTTON_H
#define SETGAMEMODEBUTTON_H

#include "UIManger/ElementsTypes/ElementsTypes.hpp"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "UIManger/UIManager.hpp"
#include "elements/base/general/StaticTouchable/StaticTouchableElement.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"
#include <SFML/System/String.hpp>
#include <concepts>
#include <optional>
#include <type_traits>

#include "UIManger/ElementsTypes/Data.hpp"

template<elements::GameMode mode>
struct elements::Info<elements::GameMode, mode> {
    static constexpr auto page = Page::START_SETTING;

    static constexpr Position get_position() {
        switch (mode) {
            case GameMode::CLASSIC :  return PositionType::DOWN;
            case GameMode::COUNT_DOWN : return PositionType::DOWN_LEFT;
            case GameMode::RACE :  return PositionType::DOWN_RIGHT_MID;
            case GameMode::SPEED : return PositionType::DOWN_LEFT_MID;
            case GameMode::TEST : return PositionType::DOWN_RIGHT;
            default: return PositionType::MID;
        }
    }

    static constexpr auto char_size = CharSizeType::M;
    static constexpr sf::String get_text() {
        switch (mode) {
            case GameMode::CLASSIC: return "Classic";
            case GameMode::COUNT_DOWN: return"Countdown";
            case GameMode::RACE: return "Race";
            case GameMode::SPEED: return "Speed";
            case GameMode::TEST: return "Test";
            default: return "";
        }
    }

};

namespace  elements {
    template<GameMode mode>
    concept game_mode_type =
        initilized_type<GameMode, mode> &&
        has_position<GameMode, mode> &&
        std::is_same_v<std::remove_cv_t<decltype(Info<GameMode, mode>::char_size)>, CharSizeType>  &&
        requires{{ Info<GameMode, mode>::get_text() } -> std::convertible_to<sf::String>;};

    using SetGameModeState = std::optional<GameMode>;


    template<GameMode mode>
    requires game_mode_type<mode>
    class SetGameModeButton final : public PageElement<Page::START_SETTING>,
                                    public StaticTouchableElement<SetGameModeState>,
                                    public UITracker {

    using Info = Info<GameMode, mode>;

    public:
        explicit SetGameModeButton(UIManager& manager) :
        StaticTouchableElement {
            manager.mode,

            { .texture = manager.texture_manager.get_set_game_mode_texture(),
            .position = PositionManager::get_position(Info::get_position())},

            { .touch_callback = [](SetGameModeState &state, MousePos) { state = mode; }}},
        UITracker(manager) {
            this->set_origin_to_centre();
            manager.texture_manager.draw_text(
                this->get_sprite(),
                Info::get_text(),
                static_cast<unsigned int>(Info::char_size));
        }
    };

    using ClassicGameModeButton = SetGameModeButton<GameMode::CLASSIC>;
    using CountDownGameModeButton = SetGameModeButton<GameMode::COUNT_DOWN>;
    using RaceGameModeButton = SetGameModeButton<GameMode::RACE>;
    using SpeedGameModeButton = SetGameModeButton<GameMode::SPEED>;
    using TestGameModeButton = SetGameModeButton<GameMode::TEST>;
}

#endif //SETGAMEMODEBUTTON_H
