//
// Created by Марсель on 29.07.2025.
//

#include "GameController.h"

#include <algorithm>
#include <ranges>

GameController::GameController(const char* argv0) : config(argv0), element_handler(config, elements) {
}

void GameController::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed) { return; }

    const auto mouse_pos = sf::Vector2f(
        static_cast<float>(event.mouseButton.x),
        static_cast<float>(event.mouseButton.y)
    );

    for (auto & obj : std::ranges::reverse_view(elements)) {
        if (!obj->enable(config.current_page) ) { continue; }

        if (!obj->get_sprite_bounds().contains(mouse_pos)) { continue; }

        if (auto* touchable = dynamic_cast<TouchableElementBase*>(obj)) {
            touchable->touch();
            return;
        }
    }
}

void GameController::update(const float dt) {
    std::ranges::for_each(elements, [&](auto& object) {
    object->update(dt);});
}

void GameController::render(sf::RenderWindow &window) {
    std::ranges::for_each(elements, [&](const auto& object) {
    if (object->enable(config.current_page)) {
        object->render(window);
    }
});
}
