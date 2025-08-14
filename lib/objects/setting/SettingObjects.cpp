//
// Created by Марсель on 03.08.2025.
//

#include "SettingObjects.h"

#include <utility>

#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"


SettingObjects::SettingObjects(
    const std::shared_ptr<sf::Texture>& base_texture,
    const std::string& text,
    const sf::Font& font,
    const sf::Vector2f scale,
    SettingCallBack callback)
: Object(set_text_on_texture(base_texture, text, font)), callback(std::move(callback)), position_scale(scale) {

}

void SettingObjects::render(sf::RenderWindow &window) const {
    sf::Sprite sprite(*texture);
    sprite.setPosition(sf::Vector2f(
        position_scale.x * static_cast<float>(window.getSize().x),
        position_scale.y * static_cast<float>(window.getSize().y)));
    if (touched) {
        sprite.setColor(sf::Color::White);
    }
    window.draw(sprite);
}

void SettingObjects::touch(Config &config) {
    touched = true;
    callback(config);
}

void SettingObjects::touch_alternative() {
    touched = false;
}
