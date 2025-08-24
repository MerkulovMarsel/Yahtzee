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
            *manager.texture_manager.get_slider_track_texture(),
            sf::Vector2f(0.,0.),
            [&](std::size_t& state, MousePos position) {
                const auto info = *manager.data.get_info<SlidersType,SliderInfo,SliderData>(sliders_type);
                float slider_texture_size = manager.texture_manager.get_slider_texture_size();
                const float cells_size = slider_texture_size / static_cast<float>(1 + info.value_max - info.value_min);
                const float mouse_x = position->x - manager.get_position(sliders_type).x + slider_texture_size / 2.f;
                state = info.value_min + static_cast<std::size_t>(mouse_x / cells_size);
            },
            [&](sf::Sprite& sprite,const std::size_t& state, bool /*unused*/) {
                const auto info = *manager.data.get_info<SlidersType,SliderInfo,SliderData>(sliders_type);
                const auto cells_count = info.value_max - info.value_min;
                const float cells_size = manager.texture_manager.get_slider_texture_size() /
                    static_cast<float>(1 + cells_count);
                const float x = manager.get_position(sliders_type).x +
                    (cells_size * (static_cast<float>(state) - static_cast<float>((info.value_max + info.value_min) / 2)));
                sprite.setPosition(x, manager.get_position(sliders_type).y);
            }
        ),
        UITracker(manager){
            this->set_origin_to_centre();
            thumb_sprite.setTexture(*manager.texture_manager.get_slider_thumb_texture());
            thumb_sprite.setOrigin(sf::Vector2f(thumb_sprite.getTexture()->getSize() / 2U));
            thumb_sprite.setPosition(manager.get_position(sliders_type));
            const auto info =  *manager.data.get_info<SlidersType,SliderInfo,SliderData>(sliders_type);
            const float slider_size = manager.texture_manager.get_slider_texture_size();
            const auto border_position = PositionManager::get_slider_border_positions(info,slider_size);
            const auto value_position = PositionManager::get_slider_value_positions(info,slider_size);
            manager.texture_manager.draw_slider_borders(thumb_sprite, border_position);
            manager.texture_manager.draw_slider_value(thumb_sprite, value_position, info);
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
