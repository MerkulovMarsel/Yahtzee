//
// Created by Марсель on 29.07.2025.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <memory>

#include "config/Config.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

// Это базовый класс всех объектов, которые рисуются

static std::shared_ptr<sf::Texture> set_text_on_texture(const std::shared_ptr<sf::Texture> &base_texture,
                                                     const std::string &text, const sf::Font& font);


#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <unordered_map>


class Element {
    sf::Sprite sprite;

    // Система анимаций
    struct Animator {
        struct Animation {
            std::vector<sf::IntRect> frames;
            float frame_duration{};
            size_t current_frame = 0;
            float elapsed_time = 0;
            bool is_playing = false;
            bool looping = false;
        };

        std::unordered_map<std::string, Animation> animations;
        std::string current_animation;

        void add_animation(const std::string& name,
                          std::vector<sf::IntRect> frames,
                          const float frame_duration) {
            animations[name] = {.frames=std::move(frames), .frame_duration=frame_duration};
        }

        void play(const std::string& name, const bool loop = true) {
            current_animation = name;
            auto& anim = animations[name];
            anim.current_frame = 0;
            anim.elapsed_time = 0;
            anim.is_playing = true;
            anim.looping = loop;
        }

        void stop() {
            if (!current_animation.empty()) {
                animations[current_animation].is_playing = false;
            }
        }

        void update(const float dt, sf::Sprite& sprite) {
            if (current_animation.empty()) { return; }
            auto& anim = animations[current_animation];
            if (!anim.is_playing) { return;}

            anim.elapsed_time += dt;
            if (anim.elapsed_time >= anim.frame_duration) {
                anim.elapsed_time = 0;
                anim.current_frame = (anim.current_frame + 1) % anim.frames.size();
                sprite.setTextureRect(anim.frames[anim.current_frame]);

                if (!anim.looping && anim.current_frame == anim.frames.size() - 1) {
                    anim.is_playing = false;
                }
            }
        }
    };

    std::unique_ptr<Animator> animator;

public:
    virtual ~Element() = default;

    explicit Element(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        const sf::Vector2f& scale = {1.f, 1.f}) : sprite(texture) {
        set_position(position);
        set_scale(scale);
    }

    [[nodiscard]] sf::Sprite& get_sprite() noexcept { return sprite; }

    void set_texture(const sf::Texture& new_texture) noexcept {
        sprite.setTexture(new_texture, true);
    }

    void set_position(const sf::Vector2f& new_position) noexcept {
        sprite.setPosition(new_position);
    }

    void set_scale(const sf::Vector2f& new_scale) noexcept {
        sprite.setScale(new_scale);
    }

    void set_color(const sf::Color& new_color) noexcept {
        sprite.setColor(new_color);
    }

    virtual bool is_current_page(Config::Page current_page) const noexcept = 0;

    void render(sf::RenderTarget& window) const {
        window.draw(sprite);
    }

    virtual void update(float dt) {
        if (animator) {
            animator->update(dt, sprite);
        }
    }


    void add_animation(const std::string& name,
                      std::vector<sf::IntRect> frames,
                      const float frame_duration) {
        if (!animator) {
            animator = std::make_unique<Animator>();
        }
        animator->add_animation(name, std::move(frames), frame_duration);
    }

    void play_animation(const std::string& name, const bool loop = true) const {
        if (animator) {
            animator->play(name, loop);
        }
    }

    void stop_animation() const {
        if (animator) {
            animator->stop();
        }
    }
};


class StaticUpdateElement : virtual public Element {
public:
    using Element::Element;

    void update(float /*dt*/) override {}
};

template <typename State>
class StateHandlerElement {
    State* state = nullptr;

public:
    virtual ~StateHandlerElement() = default;

    void set_state(State& new_state) noexcept {
        state = &new_state;
    }

    [[nodiscard]] State& get_state() const noexcept {
        return *state;
    }
};

class TouchableElementBase {
public:
    virtual ~TouchableElementBase() = default;
    virtual void touch() = 0;
};

template <typename State>
class TouchableElement : public TouchableElementBase,
                         public StateHandlerElement<State> {
    using TouchCallback = std::function<void(State&)>;
    using CheckActivity = std::function<bool(const State&)>;

    TouchCallback touch_callback;
    CheckActivity check_activity;

public:
    explicit TouchableElement(TouchCallback touch_cb,
                    CheckActivity check_active = [](const State&){ return true; })
        : touch_callback(std::move(touch_cb))
        , check_activity(std::move(check_active)) {}

    void touch() override {
        if (this->state && touch_callback && check_activity(this->get_state())) {
            touch_callback(this->get_state());
        }
    }
};

template <Config::Page page, typename State>
class StaticTouchableElement final : public StaticUpdateElement,
                                     public TouchableElement<State> {
public:
    StaticTouchableElement(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        typename TouchableElement<State>::TouchCallback touch_cb,
        typename TouchableElement<State>::CheckActivity check_active = [](const State&){ return true; },
        const sf::Vector2f& scale = {1.f, 1.f})
        : Element(texture, position, scale)
        , StaticUpdateElement()
        , TouchableElement<State>(std::move(touch_cb), std::move(check_active)) {}

    bool is_current_page(Config::Page current_page) const noexcept override {
        return current_page == page;
    }
};

template <Config::Page page, typename State>
class DynamicTouchableElement final : public Element,
                                      public TouchableElement<State> {
    using UpdateFunction = std::function<void(sf::Sprite&, const State&, bool)>;

    UpdateFunction update_function;

public:
    DynamicTouchableElement(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        typename TouchableElement<State>::TouchCallback touch_cb,
        UpdateFunction update_func,
        typename TouchableElement<State>::CheckActivity check_active = [](const State&){ return true; },
        const sf::Vector2f& scale = {1.f, 1.f})
        : Element(texture, position, scale)
        , TouchableElement<State>(std::move(touch_cb), std::move(check_active))
        , update_function(std::move(update_func)) {}

    bool is_current_page(Config::Page current_page) const noexcept override {
        return current_page == page;
    }

    void update(const float dt) override {
        Element::update(dt);

        if (update_function && this->state) {
            const State& state = this->get_state();
            bool is_active = this->check_activity(state);
            update_function(this->get_sprite(), state, is_active);
        }
    }
};

template <Config::Page page>
class StaticElement : public StaticUpdateElement {
public:
    StaticElement(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        const sf::Vector2f& scale = {1.f, 1.f})
        : Element(texture, position, scale), StaticUpdateElement() {
    }

    bool is_current_page(const Config::Page current_page) const noexcept override {
        return current_page == page;
    }
};

template<typename Actions, typename... Implementations>
requires std::is_enum_v<Actions>
class SpecialEventHandler {
    std::tuple<Implementations...> implementations;
public:
    template <Actions action, typename... Args>
    void execute(Args&&... args) {
        auto& impl = std::get<static_cast<std::size_t>(action)>(implementations);
        if (impl) {
            impl(std::forward<Args>(args)...);
        }
    }
};

#endif //OBJECT_H
