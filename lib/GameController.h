//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <memory>

#include "config/Config.h"
#include "core/game.h"
#include "element/Element.h"
#include "element/handler/Handler.h"
#include "SFML/Graphics/RenderWindow.hpp"


class GameController {
    std::unique_ptr<Game> game;
    Config config;
    Handler::Elements elements;
    Handler element_handler;

public:

    explicit GameController(const char *argv0);

    void handleEvent(const sf::Event & event);

    void update(float dt);

    void render(sf::RenderWindow & window);
};



#endif //GAMECONTROLLER_H
