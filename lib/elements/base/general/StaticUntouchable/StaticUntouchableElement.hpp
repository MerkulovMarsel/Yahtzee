//
// Created by Марсель on 21.08.2025.
//

#ifndef STATICUNOUCHABLEELEMENT_H
#define STATICUNOUCHABLEELEMENT_H

#include "elements/base/interfaces/element/static/StaticUpdateElement.hpp"


class StaticUntouchableElement : public StaticUpdateElement {
public:
    explicit StaticUntouchableElement(
        const SpriteInfo& info)
        : StaticUpdateElement(info) {
    }
};

#endif //STATICUNOUCHABLEELEMENT_H
