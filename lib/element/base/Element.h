//
// Created by Марсель on 29.07.2025.
//

#ifndef OBJECT_H
#define OBJECT_H
#include <memory>

#include "UIManger/UIManager.h"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#include "Animator/Animator.h"
#include "Touchable/TouchableElement.h"


class Element {
protected:
    sf::Sprite sprite;
    std::unique_ptr<Animator> animator;

public:
    virtual ~Element() = default;
    Element() = delete;

    explicit Element(
        const sf::Texture& texture,
        const sf::Vector2f& position,
        const sf::Vector2f& scale);


    [[nodiscard]] sf::Sprite& get_sprite() noexcept;
    [[nodiscard]] virtual sf::FloatRect get_sprite_bounds() const noexcept;


    void set_texture(const sf::Texture& new_texture) noexcept;
    void set_position(const sf::Vector2f& new_position) noexcept;
    void set_scale(const sf::Vector2f& new_scale) noexcept;
    void set_color(const sf::Color& new_color) noexcept;

    virtual bool enable(Page current_page) const noexcept = 0;
    virtual void render(sf::RenderTarget& window) const;
    virtual void update(float dt);

    void add_animation(const std::string& name,
                      std::vector<sf::IntRect> frames,
                      float frame_duration);

    void play_animation(const std::string& name, bool loop = true) const;
    void stop_animation() const;
};



#endif //OBJECT_H
