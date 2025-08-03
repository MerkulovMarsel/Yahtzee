//
// Created by Марсель on 01.08.2025.
// upd: Pasha on 03.08.2025
//

#include "ClassicGame.h"

#include <random>
#include <bits/random.h>

// good generator of the prime numbers
static thread_local std::mt19937 rng(std::random_device{}());

GameConfig::Dices ClassicGame::get_dices(std::size_t player_index) const {
    // текущие значения кубиков для указанного игрока
    return players_[player_index].dices;
}

void ClassicGame::toggle_dice(std::size_t player_index, std::size_t dice_index) {
    // Переключить состояние кубика (заморозка/разморозка)
    // Например, можно хранить флаги замороженных кубиков
}

void ClassicGame::roll(std::size_t player_index) {

}