//
// Created by Марсель on 17.08.2025.
//

#ifndef HANDLER_H
#define HANDLER_H
#include "UIManger/UIManager.h"
#include "../base/Element.h"
#include "BackGround/BackGround.h"
#include "IntegerSlider/IntegerSlider.h"
#include "PageChangerButton/PageChangerButton.h"
#include "SetPlayerCountButton/SetPlayerCountButton.h"
#include "Text/TextElement.h"
#include <vector>

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
    elements::BackToStartSettingsFromConfigSettingsButton back_to_start_button;
    elements::SinglePlayerButton single_player_button;
    elements::OneVsOnePlayerButton one_vs_one_player_button;
    elements::DiceCountSlider dice_count_slider;

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
        back_to_start_button(manager),
        single_player_button(manager),
        one_vs_one_player_button(manager),
        dice_count_slider(manager)
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
            &back_to_start_button,
            &single_player_button,
            &one_vs_one_player_button,
            &dice_count_slider
        };
    }
};




#endif //HANDLER_H
