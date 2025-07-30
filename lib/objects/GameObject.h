//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML/Graphics/RenderWindow.hpp"

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void render(sf::RenderWindow&) const  = 0;
};


#endif //GAMEOBJECT_H
