//
// Created by Марсель on 21.08.2025.
//

#include "Element.h"
#include "Animator/Animator.h"

Element::Element(
    const sf::Texture& texture,
    const sf::Vector2f& position,
    const sf::Vector2f& scale) : sprite(texture)
{
    set_position(position);
    set_scale(scale);
}

sf::Sprite& Element::get_sprite() noexcept {
    return sprite;
}

sf::FloatRect Element::get_sprite_bounds() const noexcept {
    return sprite.getGlobalBounds();
}

void Element::set_texture(const sf::Texture& new_texture) noexcept {
    sprite.setTexture(new_texture, true);
}

void Element::set_position(const sf::Vector2f& new_position) noexcept {
    sprite.setPosition(new_position);
}

void Element::set_scale(const sf::Vector2f& new_scale) noexcept {
    sprite.setScale(new_scale);
}

void Element::set_color(const sf::Color& new_color) noexcept {
    sprite.setColor(new_color);
}

void Element::set_origin_to_centre() noexcept {
    sprite.setOrigin(sf::Vector2f(sprite.getTexture()->getSize() / 2U));
}

void Element::render(sf::RenderTarget& window) const {
    window.draw(sprite);
}

void Element::update(float dt) {
    if (animator) {
        animator->update(dt, sprite);
    }
}

void Element::add_animation(const std::string& name,
                           std::vector<sf::IntRect> frames,
                           float frame_duration) {
    if (!animator) {
        animator = std::make_unique<Animator>();
    }
    animator->add_animation(name, std::move(frames), frame_duration);
}

void Element::play_animation(const std::string& name, bool loop) const {
    if (animator) {
        animator->play(name, loop);
    }
}

void Element::stop_animation() const {
    if (animator) {
        animator->stop();
    }
}