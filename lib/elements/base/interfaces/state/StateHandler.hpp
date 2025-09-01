//
// Created by Марсель on 21.08.2025.
//

#ifndef STATEHANDLER_H
#define STATEHANDLER_H

template<typename State>
class StateHandlerBase {
public:
    virtual ~StateHandlerBase() = default;

    virtual void set_state(State& new_state) = 0;

    virtual State& get_state() const = 0;
};


template <typename State>
class StateHandler : public virtual StateHandlerBase<State> {
    State* state = nullptr;

public:

    explicit StateHandler(State& state) : state(&state) {}

    void set_state(State& new_state) override {
        state = &new_state;
    }

    [[nodiscard]] State& get_state() const override {
        return *state;
    }
};

#endif //STATEHANDLER_H
