//
// Created by Марсель on 29.07.2025.
//

#include "GameController.h"

GameController::GameController() {}

void GameController::handleEvent(const sf::Event &event) {
    switch (config.current_page) {
        case Config::Page::START_SETTING : {

            break;
        }
        case Config::Page::CONFIG_SETTINGS : {

            break;
        }
        case Config::Page::GAME_PLAYING : {

            break;
        }
        case Config::Page::GAME_OVER : {
            break;
        }
    }
}

void GameController::update(const float dt) {
    std::apply([&](const std::unique_ptr<Element>& object){object->update(dt);},
        objects );
}

void GameController::render(sf::RenderWindow &window) {
    std::apply([&](const std::unique_ptr<Element>& object) {
        if  (object->is_current_page(state.current_page)) {
            object->render(window);
        }
    },
        objects );
}
