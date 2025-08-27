//
// Created by Марсель on 21.08.2025.
//

#ifndef TOUCHABLEELEMENT_H
#define TOUCHABLEELEMENT_H
#include <functional>
#include <optional>

#include "elements/base/interfaces/state/StateHandler.hpp"
#include "SFML/System/Vector2.hpp"


class TouchableElementBase {
public:
    virtual ~TouchableElementBase() = default;
    virtual void touch(std::optional<sf::Vector2f> mouse_position) = 0;
};

template <typename State>
class TouchableElement : public TouchableElementBase,
                         public virtual StateHandlerBase<State> {


public:
    using TouchCallback = std::function<void(State&, const std::optional<sf::Vector2f>&)>;
    using CheckActivity = std::function<bool(const State&)>;
    using EnableChecker = std::function<bool(const State&)>;

    struct TouchableInfo {
        TouchCallback touch_callback;
        CheckActivity check_activity = [] (const State&) { return true; };
        EnableChecker enable_checker = [] (const State&) { return true; };
    };

private:
    TouchableInfo info;
public:

    explicit TouchableElement(const TouchableInfo& info) : info(info) {}

    void touch(std::optional<sf::Vector2f> mouse_position) override {
        if (is_enable(this->get_state()) && is_active(this->get_state()) && info.touch_callback) {
            info.touch_callback(this->get_state(),  mouse_position);
        }
    }

    [[nodiscard]] bool is_enable(const State& state) const noexcept {
        return info.enable_checker(state);
    }

    [[nodiscard]] bool is_active(const State& state) const noexcept {
        return info.check_activity(state);
    }
};

#endif //TOUCHABLEELEMENT_H
