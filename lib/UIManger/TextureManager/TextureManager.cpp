//
// Created by Марсель on 19.08.2025.
//

#include "TextureManager.h"

#include <utility>

#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

fs::path TextureManager::find_assets_dir(const char *argv0) {
    const fs::path exe_path = fs::absolute(argv0).parent_path();

    const std::vector possible_paths = {
        exe_path / "assets",
        exe_path.parent_path() / "assets",
        exe_path.parent_path().parent_path() / "assets"
    };

    for (const auto& path : possible_paths) {
        if (fs::exists(path)) {
            return path;
        }
    }


    return "assets";
}

bool TextureManager::load_all_textures() {
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
                   load_texture(SLIDER_TRACK, elements::assets_filenames::SLIDER_TRACK) &&
                   load_texture(SLIDER_THUMB_DICE_COUNT, elements::assets_filenames::SLIDER_THUMB_DICE_COUNT) &&
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

bool TextureManager::load_texture(const TexturePtr &texture, const fs::path &filename) const {
    return texture->loadFromFile((ASSETS_DIR / filename).string());
}

std::shared_ptr<sf::Texture> TextureManager::set_text_on_texture(const std::shared_ptr<sf::Texture> &base_texture,
    const std::string &text, const sf::Font &font, unsigned int char_size, const sf::Color &text_color) {
    if (!base_texture) { return nullptr; }

    sf::RenderTexture texture_text;
    auto size = base_texture->getSize();
    if (!texture_text.create(size.x, size.y)) {
        return base_texture; // Fallback to original
    }

    texture_text.clear(sf::Color::Transparent);
    texture_text.draw(sf::Sprite(*base_texture));

    sf::Text sf_text;
    sf_text.setFont(font);
    sf_text.setString(text);
    sf_text.setCharacterSize(char_size);
    sf_text.setFillColor(text_color);


    sf_text.setOrigin(sf_text.getLocalBounds().getSize() / 2.0f);
    sf_text.setPosition(size.x / 2.0f, size.y / 2.0f);

    texture_text.draw(sf_text);
    texture_text.display();

    return std::make_shared<sf::Texture>(texture_text.getTexture());
}

std::shared_ptr<sf::Texture> TextureManager::create_text_texture(const std::string &text, const sf::Font &font,
    unsigned int char_size, const sf::Color &text_color, const sf::Color &background_color) {
    sf::Text temp_text;
    temp_text.setFont(font);
    temp_text.setString(text);
    temp_text.setCharacterSize(char_size);

    sf::FloatRect text_bounds = temp_text.getLocalBounds();

    sf::RenderTexture texture_text;
    if (!texture_text.create(
        static_cast<unsigned int>(text_bounds.width + 2),
        static_cast<unsigned int>(text_bounds.height + 2)
    )) {
        return nullptr;
    }

    texture_text.clear(background_color);

    sf::Text sf_text;
    sf_text.setFont(font);
    sf_text.setString(text);
    sf_text.setCharacterSize(char_size);
    sf_text.setFillColor(text_color);

    sf_text.setPosition(
        -text_bounds.left + 1,
        -text_bounds.top + 1
    );

    texture_text.draw(sf_text);
    texture_text.display();

    return std::make_shared<sf::Texture>(texture_text.getTexture());
}

TextureManager::TexturePtr TextureManager::get_change_page_button_texture() const {
    return CHANGE_PAGE_BUTTON;
}

TextureManager::TexturePtr TextureManager::get_background_texture(Page page) const {
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

TextureManager::TexturePtr TextureManager::get_set_game_mode_texture(GameMode mode) const {
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

TextureManager::TexturePtr TextureManager::get_player_count_button_texture(PlayerCount type) const {
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

TextureManager::TexturePtr TextureManager::get_slider_track_texture(SlidersType type) const {
    switch (type) {
        case SlidersType::DiceCountSlider : {
            return SLIDER_TRACK;
        }
    }
    std::unreachable();
}

TextureManager::TexturePtr TextureManager::get_slider_thumb_texture(SlidersType type) const {
    switch (type) {
        case SlidersType::DiceCountSlider : {
            return SLIDER_THUMB_DICE_COUNT;
        }
    }
    std::unreachable();
}

float TextureManager::get_slider_texture_size(SlidersType type) noexcept {
    switch (type) {
        case SlidersType::DiceCountSlider : {
            return 700.f;
        }
    }
    std::unreachable();
}
