//
// Created by Марсель on 21.08.2025.
//

#ifndef SETGAMEMODEBUTTON_H
#define SETGAMEMODEBUTTON_H
#include "core/game.h"
#include "core/modes/classic/ClassicGame.h"
#include "core/modes/coundown/CountDownGame.h"
#include "core/modes/race/RaceGame.h"
#include "core/modes/speed/SpeedGame.h"
#include "core/modes/test/TestGame.h"
#include "element/base/StaticTouchable/StaticTouchableElement.h"
#include "element/handler/BackGround/BackGround.h"

namespace  elements {
    using StartGameInfo = std::tuple<std::unique_ptr<Game>,GameConfig::GameState, Page>;
    using SetGameModeButton = StaticTouchableElement<Page::START_SETTING, StartGameInfo>;

    template<GameMode mode>
    void set_game_mode(StartGameInfo& game_info);







    // definitions
    template<GameMode mode>
    void set_game_mode(StartGameInfo& game_info) {
        switch (mode) {
            case GameMode::CLASSIC : {
                std::get<0>(game_info) = std::make_unique<Game>(ClassicGame(std::get<1>(game_info)));
                break;
            }
            case GameMode::COUNT_DOWN : {
                std::get<0>(game_info) = std::make_unique<Game>(CountDownGame(std::get<1>(game_info)));
                break;
            }
            case GameMode::RACE: {
                std::get<0>(game_info) = std::make_unique<Game>(RaceGame(std::get<1>(game_info)));
                break;
            }
            case GameMode::SPEED: {
                std::get<0>(game_info) = std::make_unique<Game>(SpeedGame(std::get<1>(game_info)));
                break;
            }
            default: {
                std::get<0>(game_info) = std::make_unique<Game>(TestGame(std::get<1>(game_info)));
            }
        }

        std::get<2>(game_info) = Page::GAME_PLAYING;
    }
}

#endif //SETGAMEMODEBUTTON_H
