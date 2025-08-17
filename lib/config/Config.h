//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <filesystem>
#include <stdexcept>
#include "GameConfig/GameConfig.h"
#include "SFML/Graphics/Texture.hpp"

namespace fs = std::filesystem;

#define CONST static constexpr auto

namespace objects::assets_filenames {


    // Текстуры костей
    CONST DICE0 = "Dice0.png";
    CONST DICE1 = "Dice1.png";
    CONST DICE2 = "Dice2.png";
    CONST DICE3 = "Dice3.png";
    CONST DICE4 = "Dice4.png";
    CONST DICE5 = "Dice5.png";
    CONST DICE6 = "Dice6.png";

    // Шрифты
    CONST FONT = "font.ttf";

    // Элементы интерфейса
    CONST SQUARE_SETTING = "SquareSetting.png";
    CONST RECTANGLE_SETTING = "RectangleSetting.png";

    // Игровые элементы
    CONST GAME_BOARD = "GameBoard.png";
    CONST GAME_OVER_BOARD = "GameOverBoard.png";
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

namespace objects {
    CONST MAX_COUNT_DICE = 7ULL;
    CONST MAX_COUNT_CATEGORY = 6ULL;
}

namespace objects::coord {
    CONST X = 1300;
    CONST Y = 900;
}

struct Config {
    fs::path ASSETS_DIR;

    enum class Page : uint8_t {
        START_SETTING,
        CONFIG_SETTINGS,
        GAME_PLAYING,
        GAME_OVER
    };

    explicit Config(const char* argv0) {
        // Устанавливаем базовый путь к assets
        ASSETS_DIR = find_assets_dir(argv0);

        // Загружаем текстуры
        if (!load_all_textures()) {
            throw std::runtime_error("Failed to load textures from: " +
                                   ASSETS_DIR.string());
        }
    }

private:
    static fs::path find_assets_dir(const char* argv0) {
        const fs::path exe_path = fs::absolute(argv0).parent_path();

        // Проверяем возможные расположения assets
        const std::vector possible_paths = {
            exe_path / "assets",                     // Рядом с .exe
            exe_path.parent_path() / "assets",       // На уровень выше
            exe_path.parent_path().parent_path() / "assets"  // Для Debug сборки
        };

        for (const auto& path : possible_paths) {
            if (fs::exists(path)) {
                return path;
            }
        }

        // Если ничего не найдено, возвращаем относительный путь
        return "assets";
    }

    bool load_all_textures() {
        try {
            return load_texture(DICE0, objects::assets_filenames::DICE0) &&
                   load_texture(DICE1, objects::assets_filenames::DICE1) &&
                   load_texture(DICE2, objects::assets_filenames::DICE2) &&
                   load_texture(DICE3, objects::assets_filenames::DICE3) &&
                   load_texture(DICE4, objects::assets_filenames::DICE4) &&
                   load_texture(DICE5, objects::assets_filenames::DICE5) &&
                   load_texture(DICE6, objects::assets_filenames::DICE6) &&
                   load_texture(GAME_BOARD, objects::assets_filenames::GAME_BOARD) &&
                   load_texture(GAME_OVER_BOARD, objects::assets_filenames::GAME_OVER_BOARD) &&
                   load_texture(ACTIVE_PLAY_BUTTON, objects::assets_filenames::ACTIVE_PLAY_BUTTON) &&
                   load_texture(UNACTIVE_PLAY_BUTTON, objects::assets_filenames::UNACTIVE_PLAY_BUTTON) &&
                   load_texture(ACTIVE_ROLL_BUTTON, objects::assets_filenames::ACTIVE_ROLL_BUTTON) &&
                   load_texture(UNACTIVE_ROLL_BUTTON, objects::assets_filenames::UNACTIVE_ROLL_BUTTON) &&
                   load_texture(ACTIVE_CATEGORY, objects::assets_filenames::ACTIVE_CATEGORY) &&
                   load_texture(UNACTIVE_CATEGORY, objects::assets_filenames::UNACTIVE_CATEGORY) &&
                   load_texture(SQUARE_SETTING, objects::assets_filenames::SQUARE_SETTING) &&
                   load_texture(RECTANGLE_SETTING, objects::assets_filenames::RECTANGLE_SETTING) &&
                   load_texture(SUM1, objects::assets_filenames::SUM1) &&
                   load_texture(SUM2, objects::assets_filenames::SUM2) &&
                   load_texture(SUM3, objects::assets_filenames::SUM3) &&
                   load_texture(SUM4, objects::assets_filenames::SUM4) &&
                   load_texture(SUM5, objects::assets_filenames::SUM5) &&
                   load_texture(SUM6, objects::assets_filenames::SUM6);
        } catch (...) {
            return false;
        }
    }

    bool load_texture(sf::Texture& texture, const fs::path& filename) const {
        return texture.loadFromFile((ASSETS_DIR / filename).string());
    }

public:

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

    static sf::Vector2f get_background_position() noexcept;

    template <Page page>
    std::shared_ptr<sf::Texture> get_background_texture() const {
        if constexpr (page == Page::GAME_PLAYING) {
            return std::make_shared<sf::Texture>(GAME_BOARD);
        } else if constexpr (page == Page::GAME_OVER) {
            return std::make_shared<sf::Texture>(GAME_OVER_BOARD);
        }
        return nullptr;
    }

    Page current_page = Page::START_SETTING;
    GameConfig game_config;
};

inline sf::Vector2f Config::get_background_position() noexcept {
    return {static_cast<float>(objects::coord::X) / 2, static_cast<float>(objects::coord::Y) / 2};
}



#endif //CONFIG_H
