//
// Created by Марсель on 26.08.2025.
//

#ifndef DYNAMICELEMENT_H
#define DYNAMICELEMENT_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <functional>
#include <memory>

#include "elements/base/interfaces/element/Element.hpp"
#include "elements/base/interfaces/state/StateHandler.hpp"


template<typename State>
class DynamicUpdateElement : public Element,
                             public virtual StateHandlerBase<State> {
public:
    using UpdateFunction = std::function<void(sf::Sprite&, const State&)>;
private:
    UpdateFunction update_function;

public:

    explicit DynamicUpdateElement(
        const SpriteInfo& info,
        UpdateFunction updateFunction) :
    Element(info),
    update_function(updateFunction) {
    }

    void update(const float dt) override {
        Element::update(dt);

        if (update_function) {
            const State& state = this->get_state();
            update_function(this->get_sprite(), state);
        }
    }

};

#endif //DYNAMICELEMENT_H
