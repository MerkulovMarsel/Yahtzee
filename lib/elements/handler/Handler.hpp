//
// Created by Марсель on 17.08.2025.
//

#ifndef HANDLER_H
#define HANDLER_H
#include "UIManger/UIManager.hpp"
#include "BackGround/BackGround.hpp"
#include "IntegerSlider/IntegerSlider.hpp"
#include "PageChangerButton/PageChangerButton.hpp"
#include "Screen/ScreenElement.hpp"
#include "SetGameModeButton/SetGameModeButton.hpp"
#include "SetPlayerCountButton/SetPlayerCountButton.hpp"
#include "Text/TextElement.hpp"

struct Handler {
    using Elements = std::vector<Element*>;

    elements::StartSettingsBackGround start_settings_back_ground;
    elements::YahtzeeMainTextElement yahtzee_main_text;
    elements::ChooseGameModeTextElement choose_game_mode;

    elements::ConfigSettingsBackGround config_settings_back_ground;
    elements::SettingsTextElement settings_main_text;
    elements::PlayerCountTextElement player_count_text;
    elements::DiceCountTextElement dice_count_text;

    elements::GameBackGround game_back_ground;

    elements::GameOverBackGround game_over_back_ground;

    elements::OpenConfigSettingsFromStartSettingButton config_from_start_button;
    elements::SinglePlayerButton single_player_button;
    elements::OneVsOnePlayerButton one_vs_one_player_button;
    elements::DiceCountSlider dice_count_slider;

    elements::RollCountScreenElement roll_count_screen;


    elements::ClassicGameModeButton classic_game_mode_button;
    elements::SpeedGameModeButton speed_game_mode_button;
    elements::RaceGameModeButton race_game_mode_button;
    elements::CountDownGameModeButton count_down_game_mode_button;
    elements::TestGameModeButton test_game_mode_button;


    explicit Handler(UIManager& manager, Elements& elements) :
        start_settings_back_ground(manager),
        yahtzee_main_text(manager),
        choose_game_mode(manager),
        config_settings_back_ground(manager),
        settings_main_text(manager),
        player_count_text(manager),
        dice_count_text(manager),
        game_back_ground(manager),
        game_over_back_ground(manager),
        config_from_start_button(manager),
        single_player_button(manager),
        one_vs_one_player_button(manager),
        dice_count_slider(manager),
        roll_count_screen(manager),
        classic_game_mode_button(manager),
        speed_game_mode_button(manager),
        race_game_mode_button(manager),
        count_down_game_mode_button(manager),
        test_game_mode_button(manager)
    {
        elements = {
            &start_settings_back_ground,
            &yahtzee_main_text,
            &choose_game_mode,
            &config_settings_back_ground,
            &settings_main_text,
            &player_count_text,
            &dice_count_text,
            &game_back_ground,
            &game_over_back_ground,
            &config_from_start_button,
            &single_player_button,
            &one_vs_one_player_button,
            &dice_count_slider,
            &roll_count_screen,
            &classic_game_mode_button,
            &speed_game_mode_button,
            &race_game_mode_button,
            &count_down_game_mode_button,
            &test_game_mode_button
        };
    }
};




#endif //HANDLER_H
