//
// Created by Марсель on 05.08.2025.
//

#include "GameObject.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"


GameObject::GameObject(const sf::Vector2f pos, const std::shared_ptr<sf::Texture>& texture):
Object(texture), position_scale(pos) {

}

void GameObject::render(sf::RenderWindow &window) const {
    sf::Sprite sprite(*texture);
    sprite.setPosition(sf::Vector2f(
        position_scale.x * static_cast<float>(window.getSize().x),
        position_scale.y * static_cast<float>(window.getSize().y)));
    if (touched) {
        sprite.setColor(sf::Color::White);
    }
    window.draw(sprite);
}
