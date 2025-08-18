//
// Created by Марсель on 17.08.2025.
//

#ifndef HANDLER_H
#define HANDLER_H
#include "core/modes/classic/ClassicGame.h"
#include "core/modes/coundown/CountDownGame.h"
#include "core/modes/race/RaceGame.h"
#include "core/modes/speed/SpeedGame.h"
#include "core/modes/test/TestGame.h"
#include "element/Element.h"
#include "src/SFML/Window/Win32/CursorImpl.hpp"


namespace elements {
    using Page = Config::Page;
    using GameMode = Config::GameMode;
    using TextTypes = info::TextTypes;

    template<Page page>
    class BackGround final : public StaticElement<page> {
    public:
        explicit BackGround(const Config& config) :
        StaticElement<page>(
            *config.get_background_texture(page),
            Config::get_background_position()) {}
    };

    using StartSettingsBackGround   = BackGround<Page::START_SETTING>;
    using ConfigSettingsBackGround  = BackGround<Page::CONFIG_SETTINGS>;
    using GameBackGround            = BackGround<Page::GAME_PLAYING>;
    using GameOverBackGround        = BackGround<Page::GAME_OVER>;

    // template<TextTypes text_type>
    // class InfoTextElement final : public StaticElement<static_cast<Page>(text_type)> {
    // public:
    //     explicit InfoTextElement(const Config& config) :
    //     StaticElement<static_cast<Page>(text_type)>(
    //             , config.get_info_text_position(text_type)) {}
    // };


    template<Page page_from, Page page_to>
    class PageChangerButton final : public StaticTouchableElement<page_from, Page> {
    public:
        explicit PageChangerButton(Config& config) :
        StaticTouchableElement<page_from, Page>(
            config.current_page,
            *config.get_change_page_button_texture(),
            Config::get_change_page_button_position(),
            [](Page& page) { if (page == page_from) { page = page_to; } }
        ) {}
    };

    using OpenConfigSettingsFromStartSettingButton = PageChangerButton<Page::START_SETTING, Page::CONFIG_SETTINGS>;
    using BackToStartSettingsFromConfigSettingsButton = PageChangerButton<Page::CONFIG_SETTINGS, Page::START_SETTING>;



    // using ChooseGameMoodTextElement      = InfoTextElement<TextTypes::CHOSE_GAME_MODE>;
    // using SettingHeadTextElement         = InfoTextElement<TextTypes::SETTING_HEAD>;
    // using PLayerCountTextElement         = InfoTextElement<TextTypes::PLAYER_COUNT>;
    // using DiceCountTextElement           = InfoTextElement<TextTypes::DICE_COUNT>;
    // using RollCountTextElement           = InfoTextElement<TextTypes::ROLL_COUNT>;
    // using CategoriesTextElement          = InfoTextElement<TextTypes::CATEGORIES>;
    // using PlayersNamesTextElement        = InfoTextElement<TextTypes::PLAYERS_NAMES>;
    // using GameOverPlayersNameTextElement = InfoTextElement<TextTypes::GAME_OVER_PLAYERS_NAMES>;



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
struct Handler {
    using Elements = std::vector<Element*>;

    elements::StartSettingsBackGround start_settings_back_ground;
    elements::ConfigSettingsBackGround config_settings_back_ground;
    elements::GameBackGround game_back_ground;
    elements::GameOverBackGround game_over_back_ground;

    elements::OpenConfigSettingsFromStartSettingButton config_from_start_button;
    elements::BackToStartSettingsFromConfigSettingsButton back_to_start_button;



    explicit Handler(Config& config, Elements& elements) :
        start_settings_back_ground(config),
        config_settings_back_ground(config),
        game_back_ground(config),
        game_over_back_ground(config),
        config_from_start_button(config),
        back_to_start_button(config){
        elements.reserve(6);
        elements.push_back(&start_settings_back_ground);
        elements.push_back(&config_settings_back_ground);
        elements.push_back(&game_back_ground);
        elements.push_back(&game_over_back_ground);
        elements.push_back(&config_from_start_button);
        elements.push_back(&back_to_start_button);
    }

};




#endif //HANDLER_H
