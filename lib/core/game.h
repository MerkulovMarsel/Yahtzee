//
// Created by Марсель on 23.07.2025.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <utility>

#include "config/GameConfig/GameConfig.h"


// Это класс игры, он отвечает за логику и я думаю сделать его базовым.


class Game {

    enum SpecialEvent : std::uint8_t {
        STOP_PLAYING_EVENT
    };


    struct PlayerInfo {
        std::vector<GameConfig::ScoreType> category_scores;
        std::vector<GameConfig::Bonus> bonus_scores;
        std::vector<GameConfig::DiceValues> dices;
        std::size_t roll_count;
    };

    std::vector<PlayerInfo> players;
public:

    virtual ~Game() = default;

    explicit Game(const GameConfig& config);

    [[nodiscard]] virtual GameConfig::Dices get_dices(std::size_t player_index) const = 0;

    [[nodiscard]] virtual GameConfig::Categories get_categories(std::size_t player_index) const = 0;

    virtual void toggle_dice(std::size_t player_index, std::size_t dice_index) = 0;

    virtual void roll(std::size_t player_index) = 0;

    virtual void set_category(std::size_t player_index, std::size_t category_index) = 0;

    virtual bool is_game_over() const = 0;

    virtual void special_event(std::size_t player_index, SpecialEvent event) = 0;
};

#endif //GAME_H
