//
// Created by Марсель on 25.07.2025.
//

#include "Application.h"

#include <imgui.h>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <memory>

#include "GameController.h"
#include "config/Config.h"

void Application::run() {

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Yahtzee");
    sf::Clock frameClock;
    ImGui::SFML::Init(window);

    auto gameController = std::make_unique<GameController>();
    while (window.isOpen()) {
        sf::Event event;
        sf::Sprite sprite();

        window.draw(sprite);
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {

            }

            gameController->handleEvent(event);
        }

        const float dt = frameClock.restart().asSeconds();
        ImGui::SFML::Update(window, sf::seconds(dt));

        gameController->update(dt);

        window.clear(sf::Color(30, 30, 40));
        gameController->render(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}