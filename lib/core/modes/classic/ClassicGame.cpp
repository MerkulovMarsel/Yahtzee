//
// Created by Марсель on 01.08.2025.
// upd: Pasha on 03.08.2025
//

#include "ClassicGame.h"

#include <random>
#include <bits/random.h>

ClassicGame::ClassicGame(const GameConfig &config)
    : Game(config),
      rng(std::random_device{}())
{
    players.resize(config.players_count);
    current_player = 0;
}

void CheckOutOfRange(std::size_t player_index, std::size_t pl_count) {
    if (player_index >= pl_count) {
        throw GameException("Invalid player index: " + std::to_string(player_index));
    }
}

// текущие значения кубиков для указанного игрока
std::vector<GameConfig::Dices> ClassicGame::get_dices(std::size_t player_index) const {
    CheckOutOfRange(player_index, players.size());
    return players[player_index].dices;
}

GameConfig::Categories ClassicGame::get_categories(std::size_t player_index) const {
    CheckOutOfRange(player_index, players.size());

    GameConfig::Categories categories;
}

std::vector<GameConfig::ScoreType> ClassicGame::get_score_table() const noexcept {
    std::vector<GameConfig::ScoreType> scores;
    for (const auto &player: players) {
        GameConfig::ScoreType total = 0;

        // Сумма по категориям
        for (auto score: player.category_scores) {
            if (score.first != std::nullopt) {
                total += score.first.value();
            }
        }

        // бонусы
        for (auto bonus: player.bonus_scores) {
            // total += (bonus.calc_score(players[player_index].category_scores) >= bonus.threshold) ? bonus.bonus : 0ull;
        }

        scores.emplace_back(total);
    }
    return scores;
}

void ClassicGame::toggle_dice(std::size_t player_index, std::size_t dice_index) {
}

void ClassicGame::roll(std::size_t player_index) {
    // use rng() mt19937
    rng();
}

void ClassicGame::set_category(std::size_t player_index, std::size_t category_index) {
}

void ClassicGame::play(std::size_t player_index) {
}

bool ClassicGame::is_game_over() const noexcept {
    for (const auto &player: players) {
        for (auto score: player.category_scores) {
            if (score.first == std::nullopt) {
                return false;
            }
        }
    }
    return true;
}

void ClassicGame::special_event(std::size_t player_index, GameConfig::SpecialEvent event) {
    if (player_index != current_player) return;

    switch (event) {
        case GameConfig::STOP_PLAYING_EVENT:
            // TODO: next_player();
            break;
    }
}
