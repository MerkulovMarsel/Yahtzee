//
// Created by Марсель on 21.08.2025.
//

#include "Animator.hpp"
#include <utility>
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include <vector>
#include <string>

void Animator::add_animation(const std::string& name,
                             std::vector<sf::IntRect> frames,
                             const float frame_duration) {
    animations[name] = {.frames=std::move(frames), .frame_duration=frame_duration};
}

void Animator::play(const std::string& name, const bool loop) {
    current_animation = name;
    auto& anim = animations[name];
    anim.current_frame = 0;
    anim.elapsed_time = 0;
    anim.is_playing = true;
    anim.looping = loop;
}

void Animator::stop() {
    if (!current_animation.empty()) {
        animations[current_animation].is_playing = false;
    }
}

void Animator::update(const float dt, sf::Sprite& sprite) {
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