//
// Created by Марсель on 06.08.2025.
//

#include "Element.h"

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

std::shared_ptr<sf::Texture> set_text_on_texture(
    const std::shared_ptr<sf::Texture>& base_texture,
    const std::string& text,
    const sf::Font& font,
    unsigned int char_size,
    const sf::Color& text_color
) {
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

std::shared_ptr<sf::Texture> create_text_texture(
    const std::string& text,
    const sf::Font& font,
    unsigned int char_size,
    const sf::Color& text_color,
    const sf::Color& background_color
) {
    // Создаём временный текст для вычисления размеров
    sf::Text temp_text;
    temp_text.setFont(font);
    temp_text.setString(text);
    temp_text.setCharacterSize(char_size);

    // Получаем границы текста (с учётом baseline и возможных "висячих" символов)
    sf::FloatRect text_bounds = temp_text.getLocalBounds();

    // Создаём RenderTexture с размерами текста (+ небольшой отступ для безопасности)
    sf::RenderTexture texture_text;
    if (!texture_text.create(
        static_cast<unsigned int>(text_bounds.width + 2),
        static_cast<unsigned int>(text_bounds.height + 2)
    )) {
        return nullptr; // Ошибка создания текстуры
    }

    // Очищаем прозрачным (или заданным) фоном
    texture_text.clear(background_color);

    // Настраиваем основной текст
    sf::Text sf_text;
    sf_text.setFont(font);
    sf_text.setString(text);
    sf_text.setCharacterSize(char_size);
    sf_text.setFillColor(text_color);

    // Позиционируем текст с учётом его границ
    sf_text.setPosition(
        -text_bounds.left + 1, // Компенсируем смещение origin
        -text_bounds.top + 1
    );

    texture_text.draw(sf_text);
    texture_text.display();

    return std::make_shared<sf::Texture>(texture_text.getTexture());
}