//
// Created by Марсель on 21.08.2025.
//

#ifndef INTEGERSLIDER_H
#define INTEGERSLIDER_H
#include "UIManger/ElementsTypes/Data.h"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "UIManger/UIManager.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <cstddef>

#include "elements/base/general/DynamicTouchable/DynamicTouchableElement.hpp"

#define GET_INFO manager.data.get_info<SlidersType, SliderInfo, SliderData>(sliders_type)

namespace elements {

    template<SlidersType sliders_type>
    class IntegerSlider final : public PageElement<Page::CONFIG_SETTINGS>,
                                public DynamicTouchableElement<std::size_t>,
                                public UITracker {

        sf::Sprite thumb_sprite;

    public:
        explicit IntegerSlider(UIManager& manager) :
        DynamicTouchableElement(
            manager.get_slider_state(sliders_type),

            {.texture = manager.texture_manager.get_slider_track_texture(),
                .position = sf::Vector2f(0., 0.)},

                [&](sf::Sprite &sprite, const std::size_t &state) {

                const auto [value_min, value_max, value_step, _] = *GET_INFO;

                const auto cells_count = ((value_max - value_min) / value_step) + 1U;

                const float slider_texture_size = manager.texture_manager.get_slider_texture_size();

                const float cells_size = slider_texture_size / static_cast<float>(cells_count);

                const float offset = (cells_size *
                    (static_cast<float>(state) - ( static_cast<float>(value_max + value_min) / 2.f)) /
                    static_cast<float>(value_step));

                const float x =manager.get_position(sliders_type).x + offset;

                sprite.setPosition(x, manager.get_position(sliders_type).y);
            },

{.touch_callback = [&](std::size_t& state, MousePos position) {

                    const auto info = *GET_INFO;

                    const float slider_texture_size = manager.texture_manager.get_slider_texture_size();

                    const auto cells_count = ((info.value_max - info.value_min) / info.value_step) + 1U;

                    const float cells_size = slider_texture_size / static_cast<float>(cells_count);

                    const float mouse_x = position->x - manager.get_position(sliders_type).x + (slider_texture_size / 2.f);

                    state = info.value_min + static_cast<std::size_t>(mouse_x / cells_size) * info.value_step;}}
        ),
        UITracker(manager){
            this->set_origin_to_centre();

            thumb_sprite.setTexture(*manager.texture_manager.get_slider_thumb_texture());

            thumb_sprite.setOrigin(sf::Vector2f(thumb_sprite.getTexture()->getSize() / 2U));

            thumb_sprite.setPosition(manager.get_position(sliders_type));

            const auto info =  *GET_INFO;

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

#undef GET_INFO

#endif //INTEGERSLIDER_H
