//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <memory>

#include "UIManger/UIManager.hpp"
#include "core/game.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Handler.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


class GameController {
    std::unique_ptr<Game> game;
    UIManager manager;
    Handler::Elements elements;
    Handler element_handler;

public:

    explicit GameController(const char *argv0);

    void handleEvent(const sf::Event & event);

    void update(float dt);

    void render(sf::RenderWindow & window);

private:
    void init_game();
};



#endif //GAMECONTROLLER_H
