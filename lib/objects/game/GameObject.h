//
// Created by Марсель on 05.08.2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "core/game.h"
#include "objects/Object.h"


class GameObject : public Object {
protected:
    sf::Vector2f position_scale;
    std::string text;
public:
    bool interactive = false;
    bool touched = false;

    GameObject(sf::Vector2f pos, const std::shared_ptr<sf::Texture>& texture);

    void render(sf::RenderWindow &window) const override;

    virtual void touch(std::shared_ptr<Game> &game, std::size_t current_player) = 0;
};


#endif //GAMEOBJECT_H
