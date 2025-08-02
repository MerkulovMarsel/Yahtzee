//
// Created by Марсель on 03.08.2025.
//

#ifndef SPEEDGAME_H
#define SPEEDGAME_H
#include <chrono>

#include "core/game.h"

// Идея в том, что игра кончается тогда, когда заканчивается время


class SpeedGame final : public Game {
public:
    SpeedGame(const GameConfig& config, std::time_t timer);

    [[nodiscard]] GameConfig::Dices get_dices(std::size_t player_index) const override;

    [[nodiscard]] GameConfig::Categories get_categories(std::size_t player_index) const override;

    [[nodiscard]] std::vector<GameConfig::ScoreType> get_score_table() const noexcept override;

    void toggle_dice(std::size_t player_index, std::size_t dice_index) override;

    void roll(std::size_t player_index) override;

    void set_category(std::size_t player_index, std::size_t category_index) override;

    void play(std::size_t player_index) override;

    bool is_game_over() const noexcept override;

    void special_event(std::size_t player_index, GameConfig::SpecialEvent event) override;
};



#endif //SPEEDGAME_H
