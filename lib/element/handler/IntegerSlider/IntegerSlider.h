//
// Created by Марсель on 21.08.2025.
//

#ifndef INTEGERSLIDER_H
#define INTEGERSLIDER_H
#include "UIManger/ElementsTypes/Data.h"
#include "UIManger/PositionManger/PositionManager.h"
#include "UIManger/UIManager.h"
#include "element/base/DynamicTouchable/DynamicTouchableElement.h"
#include "element/base/Element.h"
#include "element/handler/Tracker.h"
#include "SFML/Graphics/Sprite.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstddef>


namespace elements {

    template<SlidersType sliders_type>
    class IntegerSlider final : public DynamicTouchableElement<Page::CONFIG_SETTINGS, std::size_t>, UITracker {
        sf::Sprite thumb_sprite;
    public:
        explicit IntegerSlider(UIManager& manager) :
        DynamicTouchableElement(
            manager.get_slider_state(sliders_type),
            *manager.texture_manager.get_slider_track_texture(sliders_type),
            sf::Vector2f(0.,0.),
            [&](std::size_t& state, MousePos position) {
                const auto info = *manager.data.get_info<SlidersType,SliderInfo,SliderData>(sliders_type);
                const float cells_size = manager.texture_manager.get_slider_texture_size(sliders_type) /
                    static_cast<float>(1 + info.value_max - info.value_min);
                const float mouse_x = position->x - manager.position_manager.get_slider_position(sliders_type).x;
                state = info.value_min + static_cast<std::size_t>(mouse_x / cells_size);
            },
            [&](sf::Sprite& sprite,const std::size_t& state, bool /*unused*/) {
                const auto info = *manager.data.get_info<SlidersType,SliderInfo,SliderData>(sliders_type);
                const auto cells_count = info.value_max - info.value_min;
                const float cells_size = manager.texture_manager.get_slider_texture_size(sliders_type) /
                    static_cast<float>(1 + cells_count);
                const float x = manager.position_manager.get_track_lowest_value_position(sliders_type, cells_count).x +
                    (cells_size * static_cast<float>(state - info.value_min));
                sprite.setPosition(x, manager.position_manager.get_track_lowest_value_position(sliders_type, cells_count).y);
            }
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

    using DiceCountSlider = IntegerSlider<SlidersType::DiceCountSlider>;

}

#endif //INTEGERSLIDER_H
