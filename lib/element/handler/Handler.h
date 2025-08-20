//
// Created by Марсель on 17.08.2025.
//

#ifndef HANDLER_H
#define HANDLER_H
#include "core/modes/classic/ClassicGame.h"
#include "core/modes/speed/SpeedGame.h"
#include "../base/Element.h"
#include "BackGround/BackGround.h"
#include "IntegerSlider/IntegerSlider.h"
#include "PageChangerButton/PageChangerButton.h"
#include "SetPlayerCountButton/SetPlayerCountButton.h"

struct Handler {
    using Elements = std::vector<Element*>;

    elements::StartSettingsBackGround start_settings_back_ground;
    elements::ConfigSettingsBackGround manager_settings_back_ground;
    elements::GameBackGround game_back_ground;
    elements::GameOverBackGround game_over_back_ground;

    elements::OpenConfigSettingsFromStartSettingButton manager_from_start_button;
    elements::BackToStartSettingsFromConfigSettingsButton back_to_start_button;

    elements::SinglePlayerButton single_player_button;
    elements::OneVsOnePlayerButton one_vs_one_player_button;

    elements::DIceCountSlider dice_count_slider;

    explicit Handler(UIManager& manager, Elements& elements) :
        start_settings_back_ground(manager),
        manager_settings_back_ground(manager),
        game_back_ground(manager),
        game_over_back_ground(manager),
        manager_from_start_button(manager),
        back_to_start_button(manager),
        single_player_button(manager),
        one_vs_one_player_button(manager),
        dice_count_slider(manager){
        elements.reserve(manager.elements_count);
        elements.emplace_back(&start_settings_back_ground);
        elements.emplace_back(&manager_settings_back_ground);
        elements.emplace_back(&game_back_ground);
        elements.emplace_back(&game_over_back_ground);
        elements.emplace_back(&manager_from_start_button);
        elements.emplace_back(&back_to_start_button);
        elements.emplace_back(&single_player_button);
        elements.emplace_back(&one_vs_one_player_button);
        elements.emplace_back(&dice_count_slider);
    }
};




#endif //HANDLER_H
