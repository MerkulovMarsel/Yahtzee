//
// Created by Марсель on 21.08.2025.
//

#ifndef STATEHANDLER_H
#define STATEHANDLER_H

template <typename State>
class StateHandlerElement {
    State* state = nullptr;

public:
    virtual ~StateHandlerElement() = default;

    explicit StateHandlerElement(State& state) : state(&state) {}

    void set_state(State& new_state) noexcept {
        state = &new_state;
    }

    [[nodiscard]] State& get_state() const noexcept {
        return *state;
    }
};

#endif //STATEHANDLER_H
