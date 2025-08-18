//
// Created by Марсель on 25.07.2025.
//

#ifndef CONFIG_H
#define CONFIG_H

#include <memory>
#include <filesystem>
#include <stdexcept>
#include <utility>

#include "GameConfig/GameConfig.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace fs = std::filesystem;

#define CONST static constexpr auto

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

namespace elements {
    CONST MODE_COUNT = 5;

    CONST MAX_COUNT_DICE = 7ULL;
    CONST MAX_COUNT_CATEGORY = 6ULL;

    inline sf::Color TOUCH_COLOR = sf::Color::Yellow;
    inline sf::Color NORMAL_COLOR = sf::Color::White;
}

namespace elements::coord {
    CONST X = 1300;
    CONST Y = 900;

    CONST MODE_BUTTON_Y = 500;
    CONST MODE_BUTTON_START_X = 300;
    CONST MODE_BUTTON_END_X = X - MODE_BUTTON_START_X;

    CONST CHANGE_PAGE_BUTTON_INDENT = 30;
    CONST CHANGE_PAGE_BUTTON_X = CHANGE_PAGE_BUTTON_INDENT;
    CONST CHANGE_PAGE_BUTTON_Y = CHANGE_PAGE_BUTTON_INDENT;

    CONST CHOOSE_MODE_BUTTON_INDENT = 30;
    CONST CHOOSE_MODE_BUTTON_HEIGHT_OF_MODES = 100;

    CONST PLAYER_COUNT_BUTTON_Y = 160;
    CONST PLAYER_COUNT_BUTTON_INDENT = 240;
    CONST PLAYER_COUNT_BUTTON_SIZE_X = 186;
};

namespace elements::info {
    CONST STANDARD_TEXT_SIZE = 24;
    enum class TextTypes : std::uint8_t {
        CHOSE_GAME_MODE         = 1,
        SETTING_HEAD            = 0,
        PLAYER_COUNT            = 0,
        DICE_COUNT              = 0,
        ROLL_COUNT              = 0,
        CATEGORIES              = 0,
        PLAYERS_NAMES           = 2,
        GAME_OVER_PLAYERS_NAMES = 3,
    };
}

struct Config {
    fs::path ASSETS_DIR;

    enum class Page : uint8_t {
        START_SETTING   = 1,
        CONFIG_SETTINGS = 0,
        GAME_PLAYING    = 2,
        GAME_OVER       = 3
    };

    enum class GameMode : std::uint8_t {
        CLASSIC,
        COUNT_DOWN,
        RACE,
        SPEED,
        TEST
    };

    enum class PlayerCount : std::uint8_t {
        SINGLE = 1,
        ONE_VS_ONE = 2
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


        return "assets";
    }

    bool load_all_textures() {
        try {
            return load_texture(DICE0, elements::assets_filenames::DICE0) &&
                   load_texture(DICE1, elements::assets_filenames::DICE1) &&
                   load_texture(DICE2, elements::assets_filenames::DICE2) &&
                   load_texture(DICE3, elements::assets_filenames::DICE3) &&
                   load_texture(DICE4, elements::assets_filenames::DICE4) &&
                   load_texture(DICE5, elements::assets_filenames::DICE5) &&
                   load_texture(DICE6, elements::assets_filenames::DICE6) &&
                   load_texture(GAME_BOARD, elements::assets_filenames::GAME_BOARD) &&
                   load_texture(GAME_OVER_BOARD, elements::assets_filenames::GAME_OVER_BOARD) &&
                   load_texture(SETTINGS_BOARD, elements::assets_filenames::SETTINGS_BOARD) &&
                   load_texture(CONFIG_BOARD, elements::assets_filenames::CONFIG_BOARD) &&
                   load_texture(CLASSIC_MODE_BUTTON, elements::assets_filenames::CLASSIC_GAME_MODE_BUTTON) &&
                   load_texture(COUNTDOWN_MODE_BUTTON, elements::assets_filenames::COUNTDOWN_GAME_MODE_BUTTON) &&
                   load_texture(RACE_MODE_BUTTON, elements::assets_filenames::RACE_GAME_MODE_BUTTON) &&
                   load_texture(SPEED_MODE_BUTTON, elements::assets_filenames::SPEED_GAME_MODE_BUTTON) &&
                   load_texture(TEST_MODE_BUTTON, elements::assets_filenames::TEST_GAME_MODE_BUTTON) &&
                   load_texture(ACTIVE_PLAY_BUTTON, elements::assets_filenames::ACTIVE_PLAY_BUTTON) &&
                   load_texture(UNACTIVE_PLAY_BUTTON, elements::assets_filenames::UNACTIVE_PLAY_BUTTON) &&
                   load_texture(ACTIVE_ROLL_BUTTON, elements::assets_filenames::ACTIVE_ROLL_BUTTON) &&
                   load_texture(UNACTIVE_ROLL_BUTTON, elements::assets_filenames::UNACTIVE_ROLL_BUTTON) &&
                   load_texture(ACTIVE_CATEGORY, elements::assets_filenames::ACTIVE_CATEGORY) &&
                   load_texture(UNACTIVE_CATEGORY, elements::assets_filenames::UNACTIVE_CATEGORY) &&
                   load_texture(SQUARE_SETTING, elements::assets_filenames::SQUARE_SETTING) &&
                   load_texture(RECTANGLE_SETTING, elements::assets_filenames::RECTANGLE_SETTING) &&
                   load_texture(CHANGE_PAGE_BUTTON, elements::assets_filenames::CHANG_PAGE_BUTTON_SETTING) &&
                   load_texture(SINGLE_PLAYER_BUTTON, elements::assets_filenames::SINGLE_PLAYER_BUTTON_SETTING) &&
                   load_texture(ONE_VS_ONE_BUTTON, elements::assets_filenames::ONE_VS_ONE_BUTTON) &&
                   load_texture(SUM1, elements::assets_filenames::SUM1) &&
                   load_texture(SUM2, elements::assets_filenames::SUM2) &&
                   load_texture(SUM3, elements::assets_filenames::SUM3) &&
                   load_texture(SUM4, elements::assets_filenames::SUM4) &&
                   load_texture(SUM5, elements::assets_filenames::SUM5) &&
                   load_texture(SUM6, elements::assets_filenames::SUM6) &&
                       font.loadFromFile((ASSETS_DIR / elements::assets_filenames::FONT).generic_string());
        } catch (...) {
            return false;
        }
    }

    bool load_texture(const std::shared_ptr<sf::Texture>& texture, const fs::path& filename) const {
        return texture->loadFromFile((ASSETS_DIR / filename).string());
    }

public:

    std::shared_ptr<sf::Texture> DICE0 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> DICE1 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> DICE2 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> DICE3 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> DICE4 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> DICE5 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> DICE6 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> GAME_BOARD = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> GAME_OVER_BOARD = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SETTINGS_BOARD = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> CONFIG_BOARD = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> CLASSIC_MODE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> COUNTDOWN_MODE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> RACE_MODE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SPEED_MODE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> TEST_MODE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> ACTIVE_PLAY_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> UNACTIVE_PLAY_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> ACTIVE_ROLL_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> UNACTIVE_ROLL_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> ACTIVE_CATEGORY = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> UNACTIVE_CATEGORY = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SQUARE_SETTING = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> RECTANGLE_SETTING = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> CHANGE_PAGE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SINGLE_PLAYER_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> ONE_VS_ONE_BUTTON = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SUM1 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SUM2 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SUM3 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SUM4 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SUM5 = std::make_shared<sf::Texture>();
    std::shared_ptr<sf::Texture> SUM6 = std::make_shared<sf::Texture>();
    sf::Font font;

    sf::Vector2f get_dice_position(std::size_t dice_index) const noexcept;
    sf::Vector2f get_category_position(std::size_t category_index) const noexcept;
    sf::Vector2f get_play_button_position() const noexcept;
    sf::Vector2f get_roll_button_position() const noexcept;
    static sf::Vector2f get_mode_position(std::size_t mode_index) noexcept;
    static sf::Vector2f get_info_text_position(elements::info::TextTypes type) noexcept;
    static sf::Vector2f get_background_position() noexcept;
    static sf::Vector2f get_set_game_mode_position(GameMode mode) noexcept;
    static sf::Vector2f get_change_page_button_position() noexcept;
    static sf::Vector2f get_count_player_button_position(PlayerCount type) noexcept;

    std::shared_ptr<sf::Texture> get_change_page_button_texture() const {
        return CHANGE_PAGE_BUTTON;
    }

    std::shared_ptr<sf::Texture> get_background_texture(const Page page) const {
        if (page == Page::GAME_PLAYING) {
            return GAME_BOARD;
        }
        if (page == Page::GAME_OVER) {
            return GAME_OVER_BOARD;
        }
        if (page == Page::CONFIG_SETTINGS) {
            return CONFIG_BOARD;
        }
        return SETTINGS_BOARD;
    }

    std::shared_ptr<sf::Texture> get_set_game_mode_texture(const GameMode mode) const {
        switch (mode) {
            case GameMode::CLASSIC : {
                return CLASSIC_MODE_BUTTON;
            }
            case GameMode::COUNT_DOWN : {
                return COUNTDOWN_MODE_BUTTON;
            }
            case GameMode::RACE: {
                return RACE_MODE_BUTTON;
            }
            case GameMode::SPEED: {
                return SPEED_MODE_BUTTON;
            }
            default: {
                return TEST_MODE_BUTTON;
            }
        }
    }

    std::shared_ptr<sf::Texture> get_player_count_button_texture(const PlayerCount type) const {
        switch (type) {
            case PlayerCount::SINGLE : {
                return SINGLE_PLAYER_BUTTON;
            }
            case PlayerCount::ONE_VS_ONE: {
                return ONE_VS_ONE_BUTTON;
            }
        }
        std::unreachable();
    }

    static std::string get_info_text(elements::info::TextTypes type) noexcept;
    static unsigned int get_info_text_size(elements::info::TextTypes type) noexcept;


    GameConfig game_config;
    Page current_page = Page::START_SETTING;
};

inline sf::Vector2f Config::get_info_text_position(const elements::info::TextTypes type) noexcept {
    switch (type) {
        case elements::info::TextTypes::CHOSE_GAME_MODE : {
            return {static_cast<float>(elements::coord::CHOOSE_MODE_BUTTON_INDENT),
                static_cast<float>(elements::coord::MODE_BUTTON_Y
                    - elements::coord::CHOOSE_MODE_BUTTON_HEIGHT_OF_MODES)};
        }
        default: {
            throw std::invalid_argument("Invalid info text type");
        }
    }
}

inline sf::Vector2f Config::get_background_position() noexcept {
    return {0.f, 0.f};
}

inline sf::Vector2f Config::get_set_game_mode_position(GameMode mode) noexcept {
    return {
        (elements::coord::MODE_BUTTON_START_X +
            (static_cast<float>(mode) *
                (static_cast<float>(elements::coord::MODE_BUTTON_END_X
                    - elements::coord::MODE_BUTTON_START_X) / elements::MODE_COUNT))),
        static_cast<float>(elements::coord::Y)};
}

inline sf::Vector2f Config::get_change_page_button_position() noexcept {
    return {static_cast<float>(elements::coord::CHANGE_PAGE_BUTTON_X) ,
        static_cast<float>(elements::coord::CHANGE_PAGE_BUTTON_Y)};
}

inline sf::Vector2f Config::get_count_player_button_position(const PlayerCount type) noexcept {
    switch (type) {
        case PlayerCount::SINGLE : {
            return {static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_INDENT),
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_Y)};
        }
        case PlayerCount::ONE_VS_ONE : {
            return {static_cast<float>(elements::coord::X     -
                    elements::coord::PLAYER_COUNT_BUTTON_INDENT  -
                    elements::coord::PLAYER_COUNT_BUTTON_SIZE_X),
                static_cast<float>(elements::coord::PLAYER_COUNT_BUTTON_Y)};
        }
    }
    std::unreachable();
}

inline std::string Config::get_info_text(elements::info::TextTypes type) noexcept {
    switch (type) {
        case elements::info::TextTypes::CHOSE_GAME_MODE : {
            return "Choose Game Mode:";
        }
        default: {
            throw std::invalid_argument("Invalid info text type");
        }
    }
}

#undef CONST
#endif //CONFIG_H
