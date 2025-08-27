//
// Created by Марсель on 21.08.2025.
//

#ifndef SETGAMEMODEBUTTON_H
#define SETGAMEMODEBUTTON_H
#include "elements/base/general/StaticTouchable/StaticTouchableElement.hpp"
#include "elements/handler/BackGround/BackGround.hpp"

namespace  elements {
    using SetGameModeState = std::optional<GameMode>;

    template<GameMode mode>
    class SetGameModeButton final : public PageElement<Page::START_SETTING>,
                                    public StaticTouchableElement<SetGameModeState>,
                                    public UITracker {

    public:
        explicit SetGameModeButton(UIManager& manager) :
        StaticTouchableElement {
            manager.mode,

            { .texture = manager.texture_manager.get_set_game_mode_texture(mode),
            .position = PositionManager::get_set_game_mode_position(mode)},

            { .touch_callback = [](SetGameModeState &state, MousePos) { state = mode; }}},
        UITracker(manager) {
        }
    };

    using ClassicGameModeButton = SetGameModeButton<GameMode::CLASSIC>;
    using CountDownGameModeButton = SetGameModeButton<GameMode::COUNT_DOWN>;
    using RaceGameModeButton = SetGameModeButton<GameMode::RACE>;
    using SpeedGameModeButton = SetGameModeButton<GameMode::SPEED>;
    using TestGameModeButton = SetGameModeButton<GameMode::TEST>;
}

#endif //SETGAMEMODEBUTTON_H
