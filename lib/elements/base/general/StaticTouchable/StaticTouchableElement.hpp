//
// Created by Марсель on 21.08.2025.
//

#ifndef STATCTOUCHABLEELEMENT_H
#define STATCTOUCHABLEELEMENT_H

#include "elements/base/interfaces/element/static/StaticUpdateElement.hpp"
#include "elements/base/interfaces/state/StateHandler.hpp"
#include "elements/base/interfaces/touchable/TouchableElement.hpp"

template <typename State>
class StaticTouchableElement  : public StateHandler<State>,
                                public StaticUpdateElement,
                                public TouchableElement<State> {


public:

    StaticTouchableElement(
        State& state,
        const SpriteInfo& sprite_info,
        const typename TouchableElement<State>::TouchableInfo& touchable_info)
        : StateHandler<State>(state), StaticUpdateElement(sprite_info)
        , TouchableElement<State>(touchable_info) {}

};

#endif //STATCTOUCHABLEELEMENT_H
