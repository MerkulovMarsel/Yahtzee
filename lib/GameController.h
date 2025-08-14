//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include <memory>

#include "config/Config.h"
#include "core/game.h"
#include "objects/Object.h"
#include "objects/background/BackGround.h"
#include "objects/game/category/Category.h"
#include "objects/game/dice/Dice.h"
#include "objects/game/play/Play.h"
#include "SFML/Graphics/RenderWindow.hpp"

struct ObjectsHandler {
    BackGround main_background;
    BackGround game_over_background;
    //
    SettingObjects config_mode_open;
    SettingObjects settings_mode_classic;
    SettingObjects settings_mode_close;
    //
    std::array<Dice, objects::MAX_COUNT_DICE> dices;
    std::array<Category, objects::MAX_COUNT_CATEGORY> categories;

    Play play_button;

};


class GameController {
public:
    using Objects = std::array<std::unique_ptr<Object>, >;
private:
    std::unique_ptr<Game> game;
    Config config;
    //ObjectsHandler objects_handler;
    Objects objects;
public:

    GameController();

    void handleEvent(const sf::Event & event);

    void update(float dt);

    void render(sf::RenderWindow & window);
};



#endif //GAMECONTROLLER_H
