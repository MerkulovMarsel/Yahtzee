//
// Created by Марсель on 21.08.2025.
//

#ifndef DYNAMICTOUCHABLEELEMENT_H
#define DYNAMICTOUCHABLEELEMENT_H

#include "elements/base/interfaces/element/Element.hpp"
#include "elements/base/interfaces/element/dynamic/DynamicUpdateElement.hpp"
#include "elements/base/interfaces/state/StateHandler.hpp"
#include "elements/base/interfaces/touchable/TouchableElement.hpp"

template <typename State>
class DynamicTouchableElement : public StateHandler<State>,
                                public DynamicUpdateElement<State>,
                                public TouchableElement<State> {
public:
    DynamicTouchableElement(
        State& state,
        const Element::SpriteInfo& sprite_info,
        const typename DynamicUpdateElement<State>::UpdateFunction& update_function,
        const typename TouchableElement<State>::TouchableInfo& touchable_info)
        :
    StateHandler<State>(state),
    DynamicUpdateElement<State>(sprite_info, update_function),
    TouchableElement<State>(touchable_info){
    }
};

#endif //DYNAMICTOUCHABLEELEMENT_H
