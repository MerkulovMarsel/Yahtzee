//
// Created by Марсель on 10.08.2025.
//

#ifndef INFO_H
#define INFO_H
#include "objects/Object.h"


class Info final : public Object {
public:
    Info() = delete;

    void render(sf::RenderWindow &window) const override;
};



#endif //INFO_H
