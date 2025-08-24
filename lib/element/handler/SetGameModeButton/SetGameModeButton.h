//
// Created by Марсель on 21.08.2025.
//

#ifndef SETGAMEMODEBUTTON_H
#define SETGAMEMODEBUTTON_H
#include "element/base/StaticTouchable/StaticTouchableElement.h"
#include "element/handler/BackGround/BackGround.h"

namespace  elements {
    using SetGameModeState = std::optional<GameMode>;

    template<GameMode mode>
    class SetGameModeButton final : public StaticTouchableElement<Page::START_SETTING, SetGameModeState>, UITracker {
    public:
        explicit SetGameModeButton(UIManager& manager) :
        StaticTouchableElement {
            manager.mode,
            *manager.texture_manager.get_set_game_mode_texture(mode),
            PositionManager::get_set_game_mode_position(mode),
            [](SetGameModeState & state, MousePos) { state = mode; }
        }, UITracker(manager) {
        }
    };

    using ClassicGameModeButton = SetGameModeButton<GameMode::CLASSIC>;
    using CountDownGameModeButton = SetGameModeButton<GameMode::COUNT_DOWN>;
    using RaceGameModeButton = SetGameModeButton<GameMode::RACE>;
    using SpeedGameModeButton = SetGameModeButton<GameMode::SPEED>;
    using TestGameModeButton = SetGameModeButton<GameMode::TEST>;
}

#endif //SETGAMEMODEBUTTON_H
