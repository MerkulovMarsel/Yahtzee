//
// Created by Марсель on 21.08.2025.
//

#ifndef INTEGERSLIDER_H
#define INTEGERSLIDER_H
#include "element/base/DynamicTouchable/DynamicTouchableElement.h"
#include "element/handler/Tracker.h"
#include "SFML/Graphics/Sprite.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"


namespace elements {
    template<SlidersType slider_type>
    void integral_slider_touch_cb(std::size_t& state, MousePos position);

    template<SlidersType slider_type>
    void integral_slider_update( sf::Sprite& sprite,const std::size_t& state, bool);

    template<SlidersType sliders_type>
    class IntegerSlider final : public DynamicTouchableElement<Page::CONFIG_SETTINGS, std::size_t>, UITracker {
        sf::Sprite thumb_sprite{};
    public:
        explicit IntegerSlider(UIManager& manager) :
        DynamicTouchableElement(
            manager.get_slider_state(sliders_type),
            *manager.texture_manager.get_slider_track_texture(sliders_type),
            sf::Vector2f(0.,0.),
            integral_slider_touch_cb<sliders_type>,
            integral_slider_update<sliders_type>
        ),
        UITracker(manager){
            thumb_sprite.setTexture(*manager.texture_manager.get_slider_thumb_texture(sliders_type));
            thumb_sprite.setPosition(PositionManager::get_slider_position(sliders_type));
        }

        [[nodiscard]] sf::FloatRect get_sprite_bounds() const noexcept override {
            return thumb_sprite.getGlobalBounds();
        }

        void render(sf::RenderTarget& window) const override {
            window.draw(thumb_sprite);
            Element::render(window);
        }
    };

    using DIceCountSlider = IntegerSlider<SlidersType::DiceCountSlider>;




    template<SlidersType slider_type>
    void integral_slider_touch_cb(std::size_t &state, MousePos position) {
        constexpr auto cells_count = static_cast<std::size_t>(slider_type);
        const float x_start = PositionManager::get_slider_position(slider_type).x;
        const std::size_t lowest_value = UIManager::get_slider_lowest_value(slider_type);
        const float cells_size = TextureManager::get_slider_texture_size(slider_type) / static_cast<float>(cells_count);
        const float mouse_x = position->x - x_start;
        state = lowest_value + static_cast<std::size_t>(mouse_x / cells_size);
    }

    template<SlidersType slider_type>
    void integral_slider_update(sf::Sprite &sprite, const std::size_t &state, bool) {
        constexpr auto cells_count = static_cast<std::size_t>(slider_type);
        const float cells_size = TextureManager::get_slider_texture_size(slider_type) / static_cast<float>(cells_count);
        const float x_lowest_value = PositionManager::get_track_lowest_value_position(slider_type).x;
        const std::size_t lowest_value = UIManager::get_slider_lowest_value(slider_type);
        const float x = x_lowest_value + (cells_size * (state - lowest_value));
        const float y = PositionManager::get_track_lowest_value_position(slider_type).y;
        sprite.setPosition(x, y);
    }

}

#endif //INTEGERSLIDER_H
