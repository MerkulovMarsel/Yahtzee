// #include <iostream>
// #include <istream>
// #include "Application.h"
//
//
// int main(int args, char** argv) {
//     try {
//         Application::run();
//     } catch (...) {
//         std::cerr << "An exception occurred!" << std::endl;
//     }
// }
//
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <iostream> // Для вывода ошибок

int main() {
    // 1. Инициализация окна SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Yahtzee");
    if (!window.isOpen()) {
        std::cerr << "Failed to create SFML window!" << std::endl;
        return 1;
    }

    // 2. Инициализация ImGui-SFML
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Failed to initialize ImGui-SFML!" << std::endl;
        return 1;
    }

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            // Обработка закрытия окна
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 3. Обновление ImGui
        ImGui::SFML::Update(window, deltaClock.restart());

        // 4. Создание интерфейса
        ImGui::Begin("Debug");
        ImGui::Text("Hello, ImGui!");
        ImGui::End();

        // 5. Отрисовка
        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    // 6. Корректное завершение
    ImGui::SFML::Shutdown();
    return 0;
}