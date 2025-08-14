//
// Created by Марсель on 07.08.2025.
//

#ifndef PLAY_H
#define PLAY_H
#include "objects/game/GameObject.h"


class Play final : public GameObject {
public:
    Play();

    void touch(std::shared_ptr<Game> &game, std::size_t current_player) override;
};



#endif //PLAY_H
