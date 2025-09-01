//
// Created by Марсель on 25.08.2025.
//

#ifndef DYNAMICUNTOUCHABLEELEMENT_H
#define DYNAMICUNTOUCHABLEELEMENT_H

#include "elements/base/interfaces/element/Element.hpp"
#include "elements/base/interfaces/element/dynamic/DynamicUpdateElement.hpp"
#include "elements/base/interfaces/state/StateHandler.hpp"

template<typename State>
class DynamicUntouchableElement : public StateHandler<State>,
                                  public DynamicUpdateElement<State>{

    using UpdateFunction = typename DynamicUpdateElement<State>::UpdateFunction;

public:
    DynamicUntouchableElement(
        State& state,
        const Element::SpriteInfo& info,
        UpdateFunction updateFunction) :
    StateHandler<State>(state),
    DynamicUpdateElement<State>(info, updateFunction) {
    }
};


#endif //DYNAMICUNTOUCHABLEELEMENT_H
