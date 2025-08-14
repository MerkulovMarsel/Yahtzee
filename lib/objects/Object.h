//
// Created by Марсель on 29.07.2025.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <memory>

#include "config/Config.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Texture.hpp"

// Это базовый класс всех объектов, которые рисуются

class Object {
protected:
    std::shared_ptr<sf::Texture> texture = nullptr;
public:
    Config::Page page;

    virtual ~Object() = default;

    explicit Object(const std::shared_ptr<sf::Texture> &texture) : texture(texture) {
    }

    virtual void render(sf::RenderWindow& window) const  = 0;

    virtual void update(const float dt) {}

    static std::shared_ptr<sf::Texture> set_text_on_texture(const std::shared_ptr<sf::Texture> &base_texture,
                                                     const std::string &text, const sf::Font& font);
};


#endif //OBJECT_H
