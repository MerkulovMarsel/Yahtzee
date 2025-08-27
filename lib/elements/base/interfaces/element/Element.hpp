//
// Created by Марсель on 29.07.2025.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>

#include "SFML/Graphics/Sprite.hpp"

#include <string>
#include <vector>

#include "animator/Animator.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"

class EnableBase {
public:
    virtual ~EnableBase() = default;

    virtual bool enable(elements::Page current_page) const noexcept = 0;
};


class Element : public virtual EnableBase {
    sf::Sprite sprite;
    std::unique_ptr<Animator> animator;

public:
    struct SpriteInfo {
        std::shared_ptr<sf::Texture> texture;
        sf::Vector2f position = {0.f, 0.f};
        sf::Vector2f scale = {1.f, 1.f};
    };

    Element() = default;

    explicit Element(const SpriteInfo& sprite_info);


    [[nodiscard]] sf::Sprite& get_sprite() noexcept;
    [[nodiscard]] virtual sf::FloatRect get_sprite_bounds() const noexcept;


    void set_texture(const sf::Texture& new_texture) noexcept;
    void set_position(const sf::Vector2f& new_position) noexcept;
    void set_scale(const sf::Vector2f& new_scale) noexcept;
    void set_color(const sf::Color& new_color) noexcept;
    void set_origin_to_centre() noexcept;

    virtual void render(sf::RenderTarget& window) const;
    virtual void update(float dt);

    void add_animation(const std::string& name,
                      std::vector<sf::IntRect> frames,
                      float frame_duration);

    void play_animation(const std::string& name, bool loop = true) const;
    void stop_animation() const;
};

template<elements::Page page>
class PageElement : virtual EnableBase {
public:
    bool enable(const elements::Page current_page) const noexcept override {
        return current_page == page;
    }
};

#endif //OBJECT_H
