//
// Created by Марсель on 21.08.2025.
//

#ifndef STATICUNOUCHABLEELEMENT_H
#define STATICUNOUCHABLEELEMENT_H
#include "element/base/StaticUpdate/StaticUpdateElement.h"
#include "UIManger/ElementsTypes/ElementsTypes.h"

template <Page page>
class StaticUntouchableElement : public StaticUpdateElement {
public:
    StaticUntouchableElement(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        const sf::Vector2f& scale = {1.f, 1.f})
        : StaticUpdateElement(texture, position, scale) {
    }

    bool enable(const Page current_page) const noexcept override {
        return current_page == page;
    }
};

#endif //STATICUNOUCHABLEELEMENT_H
