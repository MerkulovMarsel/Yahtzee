//
// Created by Марсель on 21.08.2025.
//

#ifndef STATICUPDATE_H
#define STATICUPDATE_H
#include "element/base/Element.h"


class StaticUpdateElement : public Element {
public:
    using Element::Element;

    StaticUpdateElement(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        const sf::Vector2f& scale) : Element(texture, position, scale) {}

    void update(float /*dt*/) override;
};


#endif //STATICUPDATE_H
