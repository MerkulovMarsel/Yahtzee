//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "SFML/Graphics/RenderWindow.hpp"

// Это базовый класс всех объектов, которые рисуются

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void render(sf::RenderWindow&) const  = 0;

    virtual bool touch(const sf::Event& event) const = 0;
};


#endif //GAMEOBJECT_H
