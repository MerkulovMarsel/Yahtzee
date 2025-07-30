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
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Settings");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // Переменные состояния
    enum class AppState { Settings, Game };
    AppState currentState = AppState::Settings;
    int categoryCount = 0; // 0 = не выбрано

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        // --- ОКНО НАСТРОЕК ---
        if (currentState == AppState::Settings) {
            // Центрируем окно
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(400, 200));

            ImGui::Begin("Game Settings", nullptr,
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove
            );

            // Текст вопроса
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Выберите количество категорий").x) * 0.5f);
            ImGui::Text("Выберите количество категорий");

            // Кнопки
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);
            float buttonWidth = 100.f;
            float spacing = (ImGui::GetWindowWidth() - buttonWidth * 2) / 3;

            ImGui::SetCursorPosX(spacing);
            if (ImGui::Button("6", ImVec2(buttonWidth, 60))) {
                categoryCount = 6;
                currentState = AppState::Game;
            }

            ImGui::SameLine();
            ImGui::SetCursorPosX(spacing * 2 + buttonWidth);
            if (ImGui::Button("12", ImVec2(buttonWidth, 60))) {
                categoryCount = 12;
                currentState = AppState::Game;
            }

            ImGui::End();
        }
        // --- ОСНОВНАЯ ИГРА ---
        else {
            // Здесь ваша основная игровая логика
            // categoryCount содержит выбранное значение (6 или 12)
        }

        // Отрисовка
        window.clear(sf::Color(50, 50, 50));
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}