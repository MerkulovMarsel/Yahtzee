//
// Created by Марсель on 06.08.2025.
//

#include "Dice.h"

Dice::Dice(const std::size_t index, const Config &config)
    : GameObject(config.get_dice_scale(index), std::make_shared<sf::Texture>(config.DICE0)), index(index), config(config) {
}

void Dice::touch(std::shared_ptr<Game> &game, const std::size_t current_player) {
    if (interactive) {
        game->toggle_dice(current_player, index);
        dice_state = game->get_dices(current_player)[index];
        touched = dice_state.second;
    }
}

void Dice::roll(const std::shared_ptr<Game> &game, std::size_t current_player) {
    interactive = true;
    dice_state = game->get_dices(current_player)[index];
    touched = dice_state.second;
    switch (dice_state.first) {
        case GameConfig::DiceValues::ONE: {
            texture = std::make_shared<sf::Texture>(config.DICE1);
            break;
        }
        case GameConfig::DiceValues::TWO: {
            texture = std::make_shared<sf::Texture>(config.DICE2);
            break;
        }
        case GameConfig::DiceValues::THREE: {
            texture = std::make_shared<sf::Texture>(config.DICE3);
            break;
        }
        case GameConfig::DiceValues::FOUR: {
            texture = std::make_shared<sf::Texture>(config.DICE4);
            break;
        }
        case GameConfig::DiceValues::FIVE: {
            texture = std::make_shared<sf::Texture>(config.DICE5);
            break;
        }
        case GameConfig::DiceValues::SIX: {
            texture = std::make_shared<sf::Texture>(config.DICE6);
            break;
        }
        default: {
            // TODO
            throw std::invalid_argument("Invalid Dice");
        }
    }
}

void Dice::play() {
    dice_state = {GameConfig::DiceValues::UNKNOW, false};
    touched = false;
    interactive = false;
}
