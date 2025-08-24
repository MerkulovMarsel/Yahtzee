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
    elements::ChooseGameModeElement choose_game_mode;

    elements::ConfigSettingsBackGround manager_settings_back_ground;

    elements::GameBackGround game_back_ground;


    elements::GameOverBackGround game_over_back_ground;

    elements::OpenConfigSettingsFromStartSettingButton manager_from_start_button;
    elements::BackToStartSettingsFromConfigSettingsButton back_to_start_button;

    elements::SinglePlayerButton single_player_button;
    elements::OneVsOnePlayerButton one_vs_one_player_button;

    elements::DiceCountSlider dice_count_slider;


    // elements::ClassicGameModeButton classic_game_mode_button;
    // elements::CountDownGameModeButton count_down_game_mode_button;
    // elements::SpeedGameModeButton speed_game_mode_button;
    // elements::RaceGameModeButton race_game_mode_button;
    // elements::TestGameModeButton test_game_mode_button;

    explicit Handler(UIManager& manager, Elements& elements) :
        start_settings_back_ground(manager),
        yahtzee_main_text(manager),
        choose_game_mode(manager),
        manager_settings_back_ground(manager),
        game_back_ground(manager),
        game_over_back_ground(manager),
        manager_from_start_button(manager),
        back_to_start_button(manager),
        single_player_button(manager),
        one_vs_one_player_button(manager),
        dice_count_slider(manager)
        //classic_game_mode_button(manager),
        //count_down_game_mode_button(manager),
        //speed_game_mode_button(manager),
        //race_game_mode_button(manager),
        //test_game_mode_button(manager)
        {
        elements.reserve(manager.elements_count);
        elements.emplace_back(&start_settings_back_ground);
        elements.emplace_back(&yahtzee_main_text);
        elements.emplace_back(&choose_game_mode);
        elements.emplace_back(&manager_settings_back_ground);
        elements.emplace_back(&game_back_ground);
        elements.emplace_back(&game_over_back_ground);
        elements.emplace_back(&manager_from_start_button);
        elements.emplace_back(&back_to_start_button);
        elements.emplace_back(&single_player_button);
        elements.emplace_back(&one_vs_one_player_button);
        elements.emplace_back(&dice_count_slider);
        //elements.emplace_back(&classic_game_mode_button);
        //elements.emplace_back(&count_down_game_mode_button);
        //elements.emplace_back(&speed_game_mode_button);
        //elements.emplace_back(&race_game_mode_button);
        //elements.emplace_back(&test_game_mode_button);
    }
};




#endif //HANDLER_H
