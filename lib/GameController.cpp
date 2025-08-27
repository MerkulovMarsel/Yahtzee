//
// Created by Марсель on 29.07.2025.
//

#include "GameController.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "elements/base/interfaces/touchable/TouchableElement.hpp"

#include <algorithm>
#include <optional>
#include <ranges>

GameController::GameController(const char* argv0) : manager(argv0), element_handler(manager, elements) {
}

void GameController::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed) { return; }

    const auto mouse_pos = sf::Vector2f(
        static_cast<float>(event.mouseButton.x),
        static_cast<float>(event.mouseButton.y)
    );

    for (const auto & obj : std::ranges::reverse_view(elements)) {
        if (!obj->enable(manager.current_page) ) { continue; }

        if (!obj->get_sprite_bounds().contains(mouse_pos)) { continue; }

        if (auto* touchable = dynamic_cast<TouchableElementBase*>(obj)) {
            touchable->touch(sf::Vector2f(
                static_cast<float>(event.mouseButton.x),
                static_cast<float>(event.mouseButton.y)));
            break;
        }
    }

    if (manager.mode) {
        init_game();
        manager.current_page = elements::Page::GAME_PLAYING;
        manager.mode = std::nullopt;
    }
}

void GameController::update(const float dt) {
    std::ranges::for_each(elements, [&](auto& object) {
    object->update(dt);});
}

void GameController::render(sf::RenderWindow &window) {
    std::ranges::for_each(elements, [&](const auto& object) {
    if (object->enable(manager.current_page)) {
        object->render(window);
    }
});
}

void GameController::init_game() {

}
