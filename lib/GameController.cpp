//
// Created by Марсель on 29.07.2025.
//

#include "GameController.h"

#include "SFML/Graphics/Sprite.hpp"

void GameController::handleEvent(const sf::Event &event) {
    switch (config.phase) {
        case Config::Phase::START_SETTING : {

            break;
        }
        case Config::Phase::GAME_PLAYING : {
            break;
        }
        case Config::Phase::GAME_OVER : {
            break;
        }
    }
}

void GameController::update(float dt) {

}

void GameController::render(sf::RenderWindow &window) {
    // std::apply([&](const std::unique_ptr<GameObject>& object){object->render(window);},
    //     objects );
}
