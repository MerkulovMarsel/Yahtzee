//
// Created by Марсель on 07.08.2025.
//

#ifndef CATEGORY_H
#define CATEGORY_H
#include "objects/game/GameObject.h"

class Category final : public GameObject {


public:

    void touch(std::shared_ptr<Game> &game, std::size_t current_player) override;

    void touch_alternative();
};



#endif //CATEGORY_H
