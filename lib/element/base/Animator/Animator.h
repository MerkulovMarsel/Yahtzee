//
// Created by Марсель on 21.08.2025.
//

#ifndef ANIMATOR_H
#define ANIMATOR_H
#include <string>
#include <unordered_map>
#include <vector>

#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Sprite.hpp"


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
                      const float frame_duration);

    void play(const std::string& name, bool loop = true);

    void stop();

    void update(const float dt, sf::Sprite& sprite);
};



#endif //ANIMATOR_H
