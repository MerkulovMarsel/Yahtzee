//
// Created by Марсель on 22.08.2025.
//

#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "UIManger/UIManager.h"
#include "element/base/StaticUntouchable/StaticUntouchableElement.h"
#include "element/handler/Tracker.h"

namespace elements {

    template<TextType type>
    class TextElement final : public StaticUntouchableElement<get_text_page<type>()>, UITracker {
    public:
        explicit TextElement(const UIManager& manager) :
            StaticUntouchableElement<get_text_page<type>()>(
        *manager.texture_manager.get_text_background_texture(type, manager.data),
        manager.position_manager.get_position<TextType>(manager.data, type)
        ), UITracker(manager) {
            this->set_origin_to_centre();
            const auto [text, char_size] = *manager.data.get_info<TextType, TextInfo, TextData>(type);
           manager.texture_manager.draw_text(
                this->get_sprite(),text, static_cast<unsigned int>(char_size));
        }
    };

    using YahtzeeMainTextElement = TextElement<TextType::YahtzeeMain>;
    using ChooseGameModeElement = TextElement<TextType::ChooseGameMode>;
}
#endif //TEXTELEMENT_H
