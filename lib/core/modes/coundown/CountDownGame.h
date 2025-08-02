//
// Created by Марсель on 03.08.2025.
//

#ifndef COUNTDOWNGAME_H
#define COUNTDOWNGAME_H
#include "core/game.h"

// игра с определенным количеством ходов

class CountDownGame final : public Game {
public:
    CountDownGame(const GameConfig& config, std::size_t steps_count);

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



#endif //COUNTDOWNGAME_H
