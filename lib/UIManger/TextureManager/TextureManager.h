//
// Created by Марсель on 19.08.2025.
//

#ifndef TEXTUREMANGER_H
#define TEXTUREMANGER_H

#include <memory>
#include <filesystem>

#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "UIManger/ElementsTypes/Data.h"

#define CONST static constexpr auto
#define TEXTURE(NAME) std::shared_ptr<sf::Texture> NAME = std::make_shared<sf::Texture>();
namespace fs = std::filesystem;

namespace elements::assets_filenames {

    // Текстуры костей
    CONST DICE0 = "Dice0.png";
    CONST DICE1 = "Dice1.png";
    CONST DICE2 = "Dice2.png";
    CONST DICE3 = "Dice3.png";
    CONST DICE4 = "Dice4.png";
    CONST DICE5 = "Dice5.png";
    CONST DICE6 = "Dice6.png";

    // Шрифты
    CONST FONT = "BebasNeue-Regular.ttf";

    // Элементы интерфейса
    CONST SQUARE_SETTING = "SquareSetting.png";
    CONST RECTANGLE_SETTING = "RectangleSetting.png";
    CONST CHANG_PAGE_BUTTON_SETTING = "ChangePageButton.png";
    CONST SINGLE_PLAYER_BUTTON_SETTING = "SinglePlayerButton.png";
    CONST ONE_VS_ONE_BUTTON = "OneVsOneButton.png";

    CONST CLASSIC_GAME_MODE_BUTTON = "ClassicGameModeButton.png";
    CONST COUNTDOWN_GAME_MODE_BUTTON = "CountDownGameModeButton.png";
    CONST RACE_GAME_MODE_BUTTON = "RaceGameModeButton.png";
    CONST SPEED_GAME_MODE_BUTTON = "SpeedGameModeButton.png";
    CONST TEST_GAME_MODE_BUTTON = "TestGameModeButton.png";

    CONST SLIDER_TRACK = "SliderTrack.png";
    CONST SLIDER_THUMB = "SliderThumbDiceCount.png";
    CONST SLIDER_BORDER = "SliderBorder.png";

    // Игровые элементы
    CONST GAME_BOARD = "GameBoard.png";
    CONST GAME_OVER_BOARD = "GameOverBoard.png";
    CONST SETTINGS_BOARD = "SettingsBoard.png";
    CONST CONFIG_BOARD = "ConfigBoard.png";
    CONST ACTIVE_PLAY_BUTTON = "ActivePlay.png";
    CONST UNACTIVE_PLAY_BUTTON = "UnactivePlay.png";
    CONST ACTIVE_ROLL_BUTTON = "ActiveRoll.png";
    CONST UNACTIVE_ROLL_BUTTON = "UnactiveRoll.png";
    CONST ACTIVE_CATEGORY = "ActiveCategory.png";
    CONST UNACTIVE_CATEGORY = "UnactiveCategory.png";


    // Элементы подсчета очков
    CONST SUM1 = "SUM1.png";
    CONST SUM2 = "SUM2.png";
    CONST SUM3 = "SUM3.png";
    CONST SUM4 = "SUM4.png";
    CONST SUM5 = "SUM5.png";
    CONST SUM6 = "SUM6.png";
}


class TextureManager {
    using TexturePtr = std::shared_ptr<sf::Texture>;

    fs::path ASSETS_DIR;

    TEXTURE( DICE0 )
    TEXTURE( DICE1 )
    TEXTURE( DICE2 )
    TEXTURE( DICE3 )
    TEXTURE( DICE4 )
    TEXTURE( DICE5 )
    TEXTURE( DICE6 )
    TEXTURE( GAME_BOARD )
    TEXTURE( GAME_OVER_BOARD )
    TEXTURE( SETTINGS_BOARD )
    TEXTURE( CONFIG_BOARD )
    TEXTURE( CLASSIC_MODE_BUTTON )
    TEXTURE( COUNTDOWN_MODE_BUTTON )
    TEXTURE( RACE_MODE_BUTTON )
    TEXTURE( SPEED_MODE_BUTTON )
    TEXTURE( TEST_MODE_BUTTON )
    TEXTURE( ACTIVE_PLAY_BUTTON )
    TEXTURE( UNACTIVE_PLAY_BUTTON )
    TEXTURE( ACTIVE_ROLL_BUTTON )
    TEXTURE( UNACTIVE_ROLL_BUTTON )
    TEXTURE( ACTIVE_CATEGORY )
    TEXTURE( UNACTIVE_CATEGORY )
    TEXTURE( SQUARE_SETTING )
    TEXTURE( RECTANGLE_SETTING )
    TEXTURE( CHANGE_PAGE_BUTTON )
    TEXTURE( SINGLE_PLAYER_BUTTON )
    TEXTURE( ONE_VS_ONE_BUTTON )
    TEXTURE( SLIDER_TRACK )
    TEXTURE( SLIDER_THUMB )
    TEXTURE( SLIDER_BORDER )
    TEXTURE( SUM1 )
    TEXTURE( SUM2 )
    TEXTURE( SUM3 )
    TEXTURE( SUM4 )
    TEXTURE( SUM5 )
    TEXTURE( SUM6 )
    sf::Font font;
    mutable std::vector<std::shared_ptr<sf::Texture>> generic_textures;

    // Texture utility
    static fs::path find_assets_dir(const char* argv0);

    bool load_all_textures();

    bool load_texture(const TexturePtr& texture, const fs::path& filename) const;

    TexturePtr create_texture(std::optional<std::size_t>& index) const;

    bool draw_text_on_sprite(
        sf::Sprite &sprite,
        const std::string &text,
        const sf::Font &font,
        unsigned int char_size,
        std::optional<sf::Vector2f> position = std::nullopt,
        const sf::Color &text_color = elements::TEXT_COLOR,
        sf::Color background_color = sf::Color::Transparent) const;


    bool draw_texture_on_sprite(sf::Sprite &sprite, const sf::Texture &texture, sf::Vector2f position) const;

public:
    explicit TextureManager(const char* argv0) {
        ASSETS_DIR = find_assets_dir(argv0);
        if (!load_all_textures()) {
            throw std::runtime_error("Failed to load textures from: " +
                                   ASSETS_DIR.string());
        }
    }



    // Texture getters

    TexturePtr get_change_page_button_texture() const;

    TexturePtr get_background_texture(elements::Page page) const;

    TexturePtr get_set_game_mode_texture(elements::GameMode mode) const;

    TexturePtr get_player_count_button_texture(elements::PlayerCount type) const;

    TexturePtr get_slider_track_texture() const;

    TexturePtr get_slider_thumb_texture() const;

    TexturePtr get_slider_border_texture() const;

    float get_slider_texture_size() const noexcept;

    TexturePtr get_text_background_texture(elements::TextType type, const elements::Data&) const;

    bool draw_text(sf::Sprite& sprite, const std::string& text, unsigned int char_size) const;

    bool draw_slider_borders(sf::Sprite& sprite, const std::vector<float>& positions) const;

};

#undef CONST
#undef TEXTURE

#endif //TEXTUREMANGER_H
