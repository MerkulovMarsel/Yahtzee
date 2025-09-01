//
// Created by Марсель on 25.07.2025.
//

#include "Application.hpp"

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <memory>

#include "GameController.hpp"

void Application::run(const char* argv0) {

    sf::RenderWindow window(sf::VideoMode(1300, 900), "Yahtzee");
    sf::Clock frameClock;
    ImGui::SFML::Init(window);



    GameController gameController(argv0);
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed ){
                gameController.handleEvent(event);
            }
        }

        const float dt = frameClock.restart().asSeconds();
        ImGui::SFML::Update(window, sf::seconds(dt));

        gameController.update(dt);

        static constexpr std::uint32_t PHONE_COLOR = 0;
        window.clear(sf::Color(PHONE_COLOR));


        gameController.render(window);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}