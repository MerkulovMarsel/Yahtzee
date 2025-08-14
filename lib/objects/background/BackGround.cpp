//
// Created by Марсель on 05.08.2025.
//

#include "BackGround.h"

#include "SFML/Graphics/Sprite.hpp"

void BackGround::render(sf::RenderWindow &window) const {
    sf::Sprite backGround(texture);
    const sf::Vector2u size = window.getSize();
    backGround.setScale(sf::Vector2f(
        static_cast<float>(size.x) / texture.getSize().x,
        static_cast<float>(size.y) / texture.getSize().y));
    window.draw(backGround);
}
