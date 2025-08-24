//
// Created by Марсель on 21.08.2025.
//

#ifndef DYNAMICTOUCHABLEELEMENT_H
#define DYNAMICTOUCHABLEELEMENT_H
#include "element/base/Element.h"
#include "element/base/Touchable/TouchableElement.h"

template <elements::Page page, typename State>
class DynamicTouchableElement : public Element,
                                      public TouchableElement<State> {
public:
    [[nodiscard]] sf::Sprite & get_sprite_touch() noexcept override {
        return this->get_sprite();
    }

private:
    using UpdateFunction = std::function<void(sf::Sprite&, const State&, bool)>;

    UpdateFunction update_function;

public:
    bool enable(const elements::Page current_page) const noexcept override {
        return current_page == page && this->is_enable(this->get_state());
    }

    DynamicTouchableElement(
        State& state,
        const sf::Texture& texture,
        const sf::Vector2f& position,
        typename TouchableElement<State>::TouchCallback touch_cb,
        UpdateFunction update_func,
        typename TouchableElement<State>::CheckActivity check_active = [](const State&){ return true; },
        typename TouchableElement<State>::EnableChecker enable_checker = [](const State&){ return true; },
        const sf::Vector2f& scale = {1.f, 1.f})
        : Element(texture, position, scale)
        , TouchableElement<State>(state, std::move(touch_cb), std::move(check_active), std::move(enable_checker))
        , update_function(std::move(update_func)) {}

    void update(const float dt) override {
        Element::update(dt);

        if (update_function && this->get_state()) {
            const State& state = this->get_state();
            bool is_active = this->is_active(state);
            update_function(this->get_sprite(), state, is_active);
        }
    }
};

#endif //DYNAMICTOUCHABLEELEMENT_H
