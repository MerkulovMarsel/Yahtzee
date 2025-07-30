//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <memory>

#include "config/Config.h"
#include "core/game.h"
#include "objects/GameObject.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"


class GameController {
public:

    void handleEvent(const sf::Event & event);

    void update(float dt);

    void render(sf::RenderWindow & window);

private:
    // Game game;
    Config config;
    std::vector<std::unique_ptr<GameObject>> objects;
};



#endif //GAMECONTROLLER_H
