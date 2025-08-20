//
// Created by Марсель on 21.08.2025.
//

#ifndef TOUCHABLEELEMENT_H
#define TOUCHABLEELEMENT_H
#include <functional>
#include <optional>

#include "element/base/StateHandler/StateHandler.h"
#include "SFML/System/Vector2.hpp"


class TouchableElementBase {
public:
    virtual ~TouchableElementBase() = default;
    virtual void touch(std::optional<sf::Vector2f> mouse_position = std::nullopt) = 0;
};

template <typename State>
class TouchableElement : public TouchableElementBase,
                         public StateHandlerElement<State> {


public:
    using TouchCallback = std::function<void(State&, const std::optional<sf::Vector2f>&)>;
    using CheckActivity = std::function<bool(const State&)>;
    using EnableChecker = std::function<bool(const State&)>;

private:
    TouchCallback touch_callback;
    CheckActivity check_activity;
    EnableChecker enable_checker;
public:
    explicit TouchableElement(
                    State& state,
                    TouchCallback touch_cb,
                    CheckActivity check_active = [](const State&){ return true; },
                    EnableChecker enable_checker = [](const State&){ return true; })
        : StateHandlerElement<State>(state), touch_callback(std::move(touch_cb))
          , check_activity(std::move(check_active))
          , enable_checker(std::move(enable_checker)) {
    }

    void touch(std::optional<sf::Vector2f> mouse_position = std::nullopt) override {
        if (touch_callback && check_activity(this->get_state())) {
            touch_callback(this->get_state(),  mouse_position);
        }
    }

    [[nodiscard]] bool is_enable(const State& state) const noexcept {
        return this->enable_checker(state);
    }

    [[nodiscard]] bool is_active(const State& state) const noexcept {
        return this->check_activity(state);
    }

    [[nodiscard]] virtual sf::Sprite& get_sprite_touch() noexcept  = 0;
};

#endif //TOUCHABLEELEMENT_H
