//
// Created by Марсель on 21.08.2025.
//

#ifndef STATCTOUCHABLEELEMENT_H
#define STATCTOUCHABLEELEMENT_H
#include "element/base/StaticUpdate/StaticUpdateElement.h"

template <elements::Page page, typename State>
class StaticTouchableElement  : public StaticUpdateElement,
                                public TouchableElement<State> {
public:
    [[nodiscard]] sf::Sprite & get_sprite_touch() noexcept override {
        return this->get_sprite();
    }

    bool enable(const elements::Page current_page) const noexcept override {
        return current_page == page && this->is_enable(this->get_state());
    }

    StaticTouchableElement(
        State& state,
        const sf::Texture& texture,
        const sf::Vector2f& position,
        typename TouchableElement<State>::TouchCallback touch_cb,
        typename TouchableElement<State>::CheckActivity check_active = [](const State&){ return true; },
        typename TouchableElement<State>::EnableChecker  enable_checker = [](const State&){ return true; },
        const sf::Vector2f& scale = {1.f, 1.f})
        : StaticUpdateElement(texture, position, scale)
        , TouchableElement<State>(state, std::move(touch_cb), std::move(check_active), std::move(enable_checker)) {}

};

#endif //STATCTOUCHABLEELEMENT_H
