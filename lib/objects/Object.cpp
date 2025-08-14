//
// Created by Марсель on 06.08.2025.
//

#include "Object.h"

#include "config/Config.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

std::shared_ptr<sf::Texture> Object::set_text_on_texture(const std::shared_ptr<sf::Texture> &base_texture,
                                                          const std::string &text, const sf::Font &font) {
    sf::RenderTexture texture_text;
    texture_text.create(base_texture->getSize().x, base_texture->getSize().y);
    texture_text.clear(sf::Color::Transparent);
    sf::Sprite sprite(*base_texture);
    texture_text.draw(sprite);

    sf::Text text_setting;
    text_setting.setFont(font);
    text_setting.setString(text);
    text_setting.setCharacterSize(24);
    text_setting.setFillColor(sf::Color::White);
    sf::FloatRect textBounds = text_setting.getLocalBounds();
    text_setting.setOrigin(
        textBounds.left + (textBounds.width / 2.0f),
        textBounds.top + (textBounds.height / 2.0f)
    );
    text_setting.setPosition(
        static_cast<float>(texture_text.getSize().x) / 2.0f,
        static_cast<float>(texture_text.getSize().y) / 2.0f
    );

    texture_text.draw(text_setting);
    texture_text.display();

    return std::make_shared<sf::Texture>(texture_text.getTexture());
}
