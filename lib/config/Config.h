//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H
#include <cstdint>

#include "GameConfig/GameConfig.h"
#include "objects/background/BackGround.h"
#include "objects/setting/SettingObjects.h"
#include "SFML/Graphics/Texture.hpp"


#define CONST static constexpr auto

namespace objects::assets_filenames {
    CONST DICE0 = "assets/Dice0.png";
    CONST DICE1 = "assets/Dice1.png";
    CONST DICE2 = "assets/Dice2.png";
    CONST DICE3 = "assets/Dice3.png";
    CONST DICE4 = "assets/Dice4.png";
    CONST DICE5 = "assets/Dice5.png";
    CONST DICE6 = "assets/Dice6.png";


    CONST FONT = "assets/font.ttf";

    CONST SQUARE_SETTING= "assets/SquareSetting.png";
    CONST RECTANGLE_SETTING = "assets/RectangleSetting.png";


    CONST GAME_BOARD = "assets/GameBoard.png";
    CONST GAME_OVER_BOARD = "assets/GameOverBoard.png";
    CONST ACTIVE_PLAY_BUTTON = "assets/ActivePlay.png";
    CONST UNACTIVE_PLAY_BUTTON = "assets/UnactivePlay.png";
    CONST ACTIVE_ROLL_BUTTON = "assets/ActiveRoll.png";
    CONST UNACTIVE_ROLL_BUTTON = "assets/UnactiveRoll.png";
    CONST ACTIVE_CATEGORY = "assets/ActiveCategory.png";
    CONST UNACTIVE_CATEGORY = "assets/UnactiveCategory.png";

    CONST SUM1 = "assets/SUM1.png";
    CONST SUM2 = "assets/SUM2.png";
    CONST SUM3 = "assets/SUM3.png";
    CONST SUM4 = "assets/SUM4.png";
    CONST SUM5 = "assets/SUM5.png";
    CONST SUM6 = "assets/SUM6.png";
}

namespace objects {
    CONST MAX_COUNT_DICE = 7ULL;
    CONST MAX_COUNT_CATEGORY = 6ULL;

}

struct Config {
    enum class Page : uint8_t {
        START_SETTING,
        CONFIG_SETTINGS,
        GAME_PLAYING,
        GAME_OVER
    };

    Config() {
        if (!(DICE0.loadFromFile(objects::assets_filenames::DICE0) &&
              DICE1.loadFromFile(objects::assets_filenames::DICE1) &&
              DICE2.loadFromFile(objects::assets_filenames::DICE2) &&
              DICE3.loadFromFile(objects::assets_filenames::DICE3) &&
              DICE4.loadFromFile(objects::assets_filenames::DICE4) &&
              DICE5.loadFromFile(objects::assets_filenames::DICE5) &&
              DICE6.loadFromFile(objects::assets_filenames::DICE6) &&
              GAME_BOARD.loadFromFile(objects::assets_filenames::GAME_BOARD) &&
              GAME_OVER_BOARD.loadFromFile(objects::assets_filenames::GAME_OVER_BOARD) &&
              ACTIVE_PLAY_BUTTON.loadFromFile(objects::assets_filenames::ACTIVE_PLAY_BUTTON) &&
              UNACTIVE_CATEGORY.loadFromFile(objects::assets_filenames::UNACTIVE_CATEGORY) &&
              ACTIVE_ROLL_BUTTON.loadFromFile(objects::assets_filenames::ACTIVE_ROLL_BUTTON) &&
              UNACTIVE_ROLL_BUTTON.loadFromFile(objects::assets_filenames::UNACTIVE_ROLL_BUTTON) &&
              ACTIVE_CATEGORY.loadFromFile(objects::assets_filenames::ACTIVE_CATEGORY) &&
              UNACTIVE_CATEGORY.loadFromFile(objects::assets_filenames::UNACTIVE_CATEGORY) &&
              SQUARE_SETTING.loadFromFile(objects::assets_filenames::SQUARE_SETTING) &&
              RECTANGLE_SETTING.loadFromFile(objects::assets_filenames::RECTANGLE_SETTING) &&
              SUM1.loadFromFile(objects::assets_filenames::SUM1) &&
              SUM2.loadFromFile(objects::assets_filenames::SUM2) &&
              SUM3.loadFromFile(objects::assets_filenames::SUM3) &&
              SUM4.loadFromFile(objects::assets_filenames::SUM4) &&
              SUM5.loadFromFile(objects::assets_filenames::SUM5) &&
              SUM6.loadFromFile(objects::assets_filenames::SUM6))) {
            // TODO
            throw std::invalid_argument("Config::Config");
        }
    }


    sf::Texture DICE0;
    sf::Texture DICE1;
    sf::Texture DICE2;
    sf::Texture DICE3;
    sf::Texture DICE4;
    sf::Texture DICE5;
    sf::Texture DICE6;
    sf::Texture GAME_BOARD;
    sf::Texture GAME_OVER_BOARD;
    sf::Texture ACTIVE_PLAY_BUTTON;
    sf::Texture UNACTIVE_PLAY_BUTTON;
    sf::Texture ACTIVE_ROLL_BUTTON;
    sf::Texture UNACTIVE_ROLL_BUTTON;
    sf::Texture ACTIVE_CATEGORY;
    sf::Texture UNACTIVE_CATEGORY;
    sf::Texture SQUARE_SETTING;
    sf::Texture RECTANGLE_SETTING;
    sf::Texture SUM1;
    sf::Texture SUM2;
    sf::Texture SUM3;
    sf::Texture SUM4;
    sf::Texture SUM5;
    sf::Texture SUM6;


    sf::Vector2f get_dice_scale(std::size_t dice_index) const;
    sf::Vector2f get_category_scale(std::size_t category_index) const;
    sf::Vector2f get_play_button_scale() const;
    sf::Vector2f get_roll_button_scale() const;
    sf::Vector2f get_mode_scale(std::size_t mode_index) const;
    sf::Vector2f get_setting_scale(std::size_t setting_index) const;

    Page current_page = Page::START_SETTING;
    GameConfig game_config;
};


#endif //CONFIG_H
