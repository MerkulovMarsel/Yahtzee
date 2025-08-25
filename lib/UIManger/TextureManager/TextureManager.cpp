//
// Created by Марсель on 19.08.2025.
//

#include "TextureManager.h"


#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "UIManger/ElementsTypes/Data.h"

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
                   load_texture(PLAYER_COUNT_BUTTON, elements::assets_filenames::PLAYER_COUNT_BUTTON) &&
                   load_texture(SLIDER_TRACK, elements::assets_filenames::SLIDER_TRACK) &&
                   load_texture(SLIDER_THUMB, elements::assets_filenames::SLIDER_THUMB) &&
                   load_texture(SLIDER_BORDER, elements::assets_filenames::SLIDER_BORDER) &&
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

TextureManager::TexturePtr TextureManager::create_texture(std::optional<std::size_t>& index) const {
    try {
        generic_textures.push_back(std::make_shared<sf::Texture>());
        index = generic_textures.size() - 1;
        return generic_textures.back();
    } catch (...) {
        index = std::nullopt;
        return nullptr;
    }
}


bool TextureManager::draw_text_on_sprite(
    sf::Sprite &sprite,
    const std::string &text,
    const sf::Font &font,
    unsigned int char_size,
    std::optional<sf::Vector2f> position,
    const sf::Color &text_color,
    sf::Color background_color) const
{
    if (sprite.getTexture() == nullptr) {
        return false;
    }

    // Получаем размеры текстуры спрайта
    sf::Vector2u size = sprite.getTexture()->getSize();

    // Создаем временную текстуру для рендеринга
    sf::RenderTexture render_texture;
    if (!render_texture.create(size.x, size.y)) {
        return false;
    }

    // Очищаем прозрачным или указанным цветом фона
    render_texture.clear(background_color);

    // Рисуем оригинальную текстуру спрайта
    sf::Sprite original_sprite(*sprite.getTexture());
    original_sprite.setTextureRect(sprite.getTextureRect());
    render_texture.draw(original_sprite);

    // Создаем и настраиваем текст
    sf::Text sf_text;
    sf_text.setFont(font);
    sf_text.setString(text);
    sf_text.setCharacterSize(char_size);
    sf_text.setFillColor(text_color);

    // Позиционирование текста
    if (!position.has_value()) {
        // Автоматическое центрирование
        sf::FloatRect text_bounds = sf_text.getLocalBounds();
        sf_text.setOrigin(text_bounds.width / 2.0f, text_bounds.height / 2.0f);
        position = sf::Vector2f(size.x / 2.0f, size.y / 2.0f);
    }
    sf_text.setPosition(position.value());

    // Рисуем текст на временной текстуре
    render_texture.draw(sf_text);
    render_texture.display();

    // Создаем постоянную текстуру через менеджер
    std::optional<std::size_t> texture_index;
    TexturePtr permanent_texture = create_texture(texture_index);

    if (!permanent_texture) {
        return false; // Не удалось создать текстуру
    }

    // Копируем данные из временной текстуры в постоянную
    permanent_texture->loadFromImage(render_texture.getTexture().copyToImage());

    // Сохраняем оригинальные параметры спрайта
    sf::IntRect originalTextureRect = sprite.getTextureRect();
    sf::Vector2f originalOrigin = sprite.getOrigin();
    sf::Vector2f originalScale = sprite.getScale();
    float originalRotation = sprite.getRotation();

    // Обновляем текстуру спрайта
    sprite.setTexture(*permanent_texture, false); // false = не сбрасывать rect

    // Восстанавливаем оригинальные параметры
    sprite.setTextureRect(originalTextureRect);
    sprite.setOrigin(originalOrigin);
    sprite.setScale(originalScale);
    sprite.setRotation(originalRotation);

    return true;
}

bool TextureManager::draw_texture_on_sprite(sf::Sprite &sprite, const sf::Texture &texture,
                                            const sf::Vector2f position) const {
    if (sprite.getTexture() == nullptr) {
        return false;
    }

    sf::Vector2u size = sprite.getTexture()->getSize();

    sf::RenderTexture render_texture;
    if (!render_texture.create(size.x, size.y)) {
        return false;
    }
    render_texture.clear(sf::Color::Transparent);

    sf::Sprite original_sprite(*sprite.getTexture());
    original_sprite.setTextureRect(sprite.getTextureRect());
    render_texture.draw(original_sprite);

    sf::Sprite texture_sprite(texture);

    sf::Vector2f texture_center(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    texture_sprite.setOrigin(texture_center);

    texture_sprite.setPosition(position);

    render_texture.draw(texture_sprite);
    render_texture.display();

    std::optional<std::size_t> texture_index;
    TexturePtr permanent_texture = create_texture(texture_index);
    if (!permanent_texture) {
        return false;
    }

    permanent_texture->loadFromImage(render_texture.getTexture().copyToImage());

    sf::IntRect originalTextureRect = sprite.getTextureRect();
    sf::Vector2f originalOrigin = sprite.getOrigin();
    sf::Vector2f originalScale = sprite.getScale();
    float originalRotation = sprite.getRotation();

    sprite.setTexture(*permanent_texture, false);

    sprite.setTextureRect(originalTextureRect);
    sprite.setOrigin(originalOrigin);
    sprite.setScale(originalScale);
    sprite.setRotation(originalRotation);

    return true;
}


TextureManager::TexturePtr TextureManager::get_change_page_button_texture() const {
    return CHANGE_PAGE_BUTTON;
}

TextureManager::TexturePtr TextureManager::get_background_texture(elements::Page page) const {
    if (page == elements::Page::GAME_PLAYING) {
        return GAME_BOARD;
    }
    if (page == elements::Page::GAME_OVER) {
        return GAME_OVER_BOARD;
    }
    if (page == elements::Page::CONFIG_SETTINGS) {
        return CONFIG_BOARD;
    }
    return SETTINGS_BOARD;
}

TextureManager::TexturePtr TextureManager::get_set_game_mode_texture(elements::GameMode mode) const {
    switch (mode) {
        case elements::GameMode::CLASSIC : {
            return CLASSIC_MODE_BUTTON;
        }
        case elements::GameMode::COUNT_DOWN : {
            return COUNTDOWN_MODE_BUTTON;
        }
        case elements::GameMode::RACE: {
            return RACE_MODE_BUTTON;
        }
        case elements::GameMode::SPEED: {
            return SPEED_MODE_BUTTON;
        }
        default: {
            return TEST_MODE_BUTTON;
        }
    }
}

TextureManager::TexturePtr TextureManager::get_player_count_button_texture() const {
    return PLAYER_COUNT_BUTTON;
}

TextureManager::TexturePtr TextureManager::get_slider_track_texture() const {
    return SLIDER_TRACK;
}

TextureManager::TexturePtr TextureManager::get_slider_thumb_texture() const {
    return SLIDER_THUMB;
}

TextureManager::TexturePtr TextureManager::get_slider_border_texture() const {
    return SLIDER_BORDER;
}

float TextureManager::get_slider_texture_size() const noexcept {
    return SLIDER_THUMB->getSize().x;
}

TextureManager::TexturePtr TextureManager::get_text_background_texture(const elements::TextType type, const elements::Data& data) const {
    std::optional<std::size_t> index;
    TexturePtr permanent_texture = create_texture(index);

    if (!permanent_texture) {
        return nullptr;
    }

    const auto info = *data.get_info<elements::TextType, elements::TextInfo, elements::TextData>(type);
    const auto width = static_cast<unsigned int>(info.char_size) * info.text.size();
    const auto height = static_cast<unsigned int>(info.char_size);
    constexpr unsigned int loft = 50U;
    permanent_texture->create(width + loft, height + loft);
    return permanent_texture;
}

bool TextureManager::draw_text(
    sf::Sprite &sprite,
    const std::string& text,
    const unsigned int char_size,
    std::optional<sf::Vector2f> position) const {
    sf::Text sf_text;
    sf_text.setFont(font);
    sf_text.setString(text);
    sf_text.setCharacterSize(char_size);
    sf_text.setFillColor(elements::TEXT_COLOR);

    sf::FloatRect text_bounds = sf_text.getLocalBounds();

    sf::RenderTexture render_texture;
    if (!render_texture.create(
        static_cast<unsigned int>(text_bounds.width),
        static_cast<unsigned int>(text_bounds.height))
    ) {
        return false;
    }
    render_texture.clear(sf::Color::Transparent);

    sf_text.setPosition(-text_bounds.left, -text_bounds.top);

    render_texture.draw(sf_text);
    render_texture.display();

    std::optional<std::size_t> index;
    const auto permanent_texture = create_texture(index);
    if (!permanent_texture) {
        return false;
    }
    permanent_texture->loadFromImage(render_texture.getTexture().copyToImage());

    sf::Vector2u sprite_size = sprite.getTexture()->getSize();
    sf::Vector2f center_position(static_cast<float>(sprite_size.x) / 2.0f, static_cast<float>(sprite_size.y) / 2.0f);

    return draw_texture_on_sprite(sprite, *permanent_texture, position.value_or(center_position));
}

bool TextureManager::draw_slider_borders(sf::Sprite &sprite,const std::vector<float>& positions) const {
    const float y = static_cast<float>(SLIDER_THUMB->getSize().y) / 2.0f;
    for (const auto x : positions) {
        if (!draw_texture_on_sprite(sprite, *SLIDER_BORDER, sf::Vector2f(x, y))) {
            return false;
        };
    }
    return true;
}

bool TextureManager::draw_slider_value(sf::Sprite &sprite, const std::vector<float> &positions, const elements::SliderInfo &info) const {
    const float y = static_cast<float>(SLIDER_THUMB->getSize().y) / 5.0f;
    std::size_t start_value = info.value_min;
    for (const auto x : positions) {
        if (!draw_text(
            sprite,
            std::to_string(start_value),
            static_cast<unsigned int>(info.char_size),
            sf::Vector2f(x, y))) {
            return false;
        };
        start_value += info.value_step;
    }
    return true;
}

