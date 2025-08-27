//
// Created by Марсель on 23.07.2025.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <utility>

#include "UIManger/GameConfig/GameConfig.hpp"

class Game {
    struct PlayerInfo {
        std::vector<GameConfig::ScoreType> category_scores;
        std::vector<GameConfig::BonusState> bonus_scores;
        std::vector<GameConfig::DiceValues> dices;
        std::optional<std::size_t> chosen_category;
        std::size_t roll_count;
    };

    using Players = std::vector<PlayerInfo>;

    Players players;
public:

    enum class GameResult : std::uint8_t {
        UNKNOWN,
        WIN,
        SECOND_PLACE,
        THIRD_PLACE,
        LOSE
    };

    virtual ~Game() = default;

    explicit Game(const GameConfig::GameState& state);

    [[nodiscard]] virtual GameConfig::Dices get_dices(std::size_t player_index) const = 0;

    [[nodiscard]] virtual GameConfig::Categories get_categories(std::size_t player_index) const = 0;

    [[nodiscard]] virtual std::vector<GameConfig::ScoreType> get_score_table() const noexcept = 0;

    [[nodiscard]] virtual GameResult get_player_result(std::size_t player_index) const noexcept = 0;

    virtual void toggle_dice(std::size_t player_index, std::size_t dice_index) = 0;

    virtual void roll(std::size_t player_index) = 0;

    virtual void set_category(std::size_t player_index, std::size_t category_index) = 0;

    virtual void play(std::size_t player_index) = 0;

    virtual bool is_game_over() const noexcept = 0;

    virtual void special_event(std::size_t player_index, GameConfig::SpecialEvent event) = 0;
};

#endif //GAME_H
