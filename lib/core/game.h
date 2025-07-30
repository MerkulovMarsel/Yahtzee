// //
// // Created by Марсель on 23.07.2025.
// //
//
// #ifndef GAME_H
// #define GAME_H
// #include <array>
// #include <functional>
// #include <memory>
// #include <optional>
// #include <utility>
//
// #include "config/GameConfig/GameConfig.h"
//
//
// class Game {
//
//     struct PlayerInfo {
//         std::array<GameConfig::ScoreType, GameConfig::CategoryCount> category_scores;
//     };
//
//     std::vector<PlayerInfo> players;
// public:
//     Game(const GameConfig&);
//
//     [[nodiscard]] GameConfig::Dices get_dices(const std::size_t player_index) const {
//         return players[player_index].dices;
//     }
//
//     [[nodiscard]] GameConfig::Categories get_categories(const std::size_t player_index) const {
//         return players[player_index].categories;
//     }
//
//     void change_dice_block(const std::size_t player_index, const std::size_t dice_index) {
//         players[player_index].dices[dice_index].second = !players[player_index].dices[dice_index].second;
//     }
//
//     void roll(std::size_t player_index);
//
//     void set_category(std::size_t player_index, std::size_t category_index);
//
// };
//
//
//
// #endif //GAME_H
