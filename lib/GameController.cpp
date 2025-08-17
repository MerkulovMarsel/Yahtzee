//
// Created by Марсель on 29.07.2025.
//

#include "GameController.h"

#include <algorithm>

GameController::GameController(const char* argv0) : config(argv0) {
}

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
    std::ranges::for_each(objects, [&](auto& object) {
    object->update(dt);});
}

void GameController::render(sf::RenderWindow &window) {
    std::ranges::for_each(objects, [&](const auto& object) {
    if (object->is_current_page(state.current_page)) {
        object->render(window);
    }
});
}
