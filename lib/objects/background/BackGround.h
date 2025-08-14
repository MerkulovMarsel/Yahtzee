//
// Created by Марсель on 05.08.2025.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "objects/Object.h"
#include "SFML/Graphics/Text.hpp"


class BackGround final : public Object {
public:
    explicit BackGround(const sf::Texture& texture) : Object(std::make_shared<sf::Texture>(texture)) {}

    void render(sf::RenderWindow &window) const override;
};




#endif //BACKGROUND_H
