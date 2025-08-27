//
// Created by Марсель on 22.08.2025.
//

#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "UIManger/ElementsTypes/Data.h"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "UIManger/UIManager.hpp"
#include "elements/handler/Tracker.hpp"
#include "elements/base/general/StaticUntouchable/StaticUntouchableElement.hpp"

#define GET_INFO manager.data.get_info<TextType, TextInfo, TextData>(type)

namespace elements {

    template<TextType type>
    class TextElement final : public PageElement<get_text_page<type>()>,
                              public StaticUntouchableElement,
                              public UITracker {

    public:
        explicit TextElement(const UIManager& manager) :
        StaticUntouchableElement({
            .texture = manager.texture_manager.get_text_background_texture(type, manager.data),
            .position = manager.position_manager.get_position<TextType>(manager.data, type)}),
        UITracker(manager) {
            this->set_origin_to_centre();

            const auto [text, char_size] = *GET_INFO;
           manager.texture_manager.draw_text(
                this->get_sprite(),text, static_cast<unsigned int>(char_size));
        }
    };

    using YahtzeeMainTextElement = TextElement<TextType::YahtzeeMain>;
    using ChooseGameModeTextElement = TextElement<TextType::ChooseGameMode>;
    using SettingsTextElement = TextElement<TextType::Settings>;
    using PlayerCountTextElement = TextElement<TextType::PlayerCount>;
    using DiceCountTextElement = TextElement<TextType::DiceCount>;
}

#undef GET_INFO

#endif //TEXTELEMENT_H
