//
// Created by Марсель on 21.08.2025.
//

#ifndef STATICUPDATE_H
#define STATICUPDATE_H

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "elements/base/interfaces/element/Element.hpp"


class StaticUpdateElement : public Element {
public:
    using Element::Element;

    explicit StaticUpdateElement(const SpriteInfo& info) : Element(info) {}

    void update(float /*dt*/) override;
};


#endif //STATICUPDATE_H
