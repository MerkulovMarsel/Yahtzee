//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <memory>

#include "config/Config.h"
#include "core/game.h"
#include "objects/Element.h"
#include "SFML/Graphics/RenderWindow.hpp"




struct ObjectsHandler {

};


struct GameState {
    Config::Page current_page;

};

class GameController {
public:
    using Objects = std::vector<std::unique_ptr<Element>>;
private:
    std::unique_ptr<Game> game;
    Config config;
    GameState state;
    ObjectsHandler objects_handler;
    Objects objects;
public:

    GameController();

    void handleEvent(const sf::Event & event);

    void update(float dt);

    void render(sf::RenderWindow & window);
};



#endif //GAMECONTROLLER_H
