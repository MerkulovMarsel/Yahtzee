//
// Created by Марсель on 17.08.2025.
//

#include "TestGame.hpp"


GameConfig::Dices TestGame::get_dices(std::size_t player_index) const {
}

GameConfig::Categories TestGame::get_categories(std::size_t player_index) const {
}

std::vector<GameConfig::ScoreType> TestGame::get_score_table() const noexcept {
}

Game::GameResult TestGame::get_player_result(std::size_t player_index) const noexcept {
}

void TestGame::toggle_dice(std::size_t player_index, std::size_t dice_index) {
}

void TestGame::roll(std::size_t player_index) {
}

void TestGame::set_category(std::size_t player_index, std::size_t category_index) {
}

void TestGame::play(std::size_t player_index) {
}

bool TestGame::is_game_over() const noexcept {
}

void TestGame::special_event(std::size_t player_index, GameConfig::SpecialEvent event) {
}
