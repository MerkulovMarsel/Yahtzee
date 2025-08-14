//
// Created by Марсель on 06.08.2025.
//

#ifndef DICE_H
#define DICE_H
#include "config/Config.h"
#include "config/GameConfig/GameConfig.h"
#include "objects/game/GameObject.h"


class Dice final : public GameObject {
    std::size_t index;
    const Config& config;
    GameConfig::DiceState dice_state = {GameConfig::DiceValues::UNKNOW, false};
public:
    explicit Dice(std::size_t index,const Config& config);

    void touch(std::shared_ptr<Game> &game, std::size_t current_player) override;

    void roll(const std::shared_ptr<Game> &game, std::size_t current_player);

    void play();
};



#endif //DICE_H
