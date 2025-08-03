//
// Created by Марсель on 01.08.2025.
//

#ifndef SMALLCLASSICGAME_H
#define SMALLCLASSICGAME_H
#include "core/game.h"

// PASHA YOU NEED TO DO

class ClassicGame final : public Game {
public:
    ClassicGame(const GameConfig& config);

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



#endif //SMALLCLASSICGAME_H
