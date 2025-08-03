//
// Created by Марсель on 25.07.2025.
//

#include "Application.h"

#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <memory>

#include "GameController.h"

void Application::run() {

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Yahtzee");
    sf::Clock frameClock;
    ImGui::SFML::Init(window);

    auto gameController = std::make_unique<GameController>();
    while (window.isOpen()) {
        sf::Event event{};

        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            /*какие еще мы поддерживаем?*/
            if (event.type == sf::Event::MouseButtonPressed ){

                // Обрабатываем взаимодействие с игроком
                gameController->handleEvent(event);

            }
        }

        const float dt = frameClock.restart().asSeconds();
        ImGui::SFML::Update(window, sf::seconds(dt));

        //Я так понимаю можно менять анимацию в зависимости от времени,
        //но до анимации еще далеко, так что пока пусто
        gameController->update(dt);

        static constexpr std::uint32_t PHONE_COLOR = 0;
        window.clear(sf::Color(PHONE_COLOR));

        //Делает window.draw(Какой-то спрайт) по моей задумке
        gameController->render(window);

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}