//
// Created by Марсель on 22.08.2025.
//

#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "UIManger/ElementsTypes/Constant.hpp"
#include "UIManger/ElementsTypes/Data.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.hpp"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "UIManger/UIManager.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"
#include "elements/base/general/StaticUntouchable/StaticUntouchableElement.hpp"
#include <SFML/System/String.hpp>
#include <concepts>
#include <string_view>
#include <type_traits>
#include <utility>


struct TextInfo {
    elements::Page page;
    elements::CharSizeType char_size;
    elements::Position position;
    std::string_view text;

    constexpr TextInfo(const elements::Page p, const elements::CharSizeType cs,
                      elements::Position pos, const std::string_view txt)
        : page(p), char_size(cs), position(std::move(pos)), text(txt) {}
};

template<elements::TextType type>
consteval auto make_text_info() {
    static_assert(type == elements::TextType::YahtzeeMain ||
                  type == elements::TextType::ChooseGameMode ||
                  type == elements::TextType::Settings ||
                  type == elements::TextType::DiceCount ||
                  type == elements::TextType::PlayerCount,
                  "Unknown TextType");


    if constexpr (type == elements::TextType::YahtzeeMain) {
        return TextInfo{
            elements::Page::START_SETTING,
            elements::CharSizeType::XXL,
            elements::PositionType::UP,
            "Yahtzee"
        };
    }
    else if constexpr (type == elements::TextType::ChooseGameMode) {
        return TextInfo{
            elements::Page::START_SETTING,
            elements::CharSizeType::XL,
            elements::PositionType::MID,
            "Choose Game Mode"
        };
    }
    else if constexpr (type == elements::TextType::Settings) {
        return TextInfo{
            elements::Page::CONFIG_SETTINGS,
            elements::CharSizeType::L,
            elements::HighFix{elements::PositionType::MID, elements::coord::SETTINGS_TEXT_Y},
            "Settings"
        };
    }
    else if constexpr (type == elements::TextType::DiceCount) {
        return TextInfo{
            elements::Page::CONFIG_SETTINGS,
            elements::CharSizeType::M,
            elements::HighFix{elements::PositionType::MID, elements::coord::DICE_COUNT_TEXT_Y},
            "Dice Count"
        };
    }
    else if constexpr (type == elements::TextType::PlayerCount) {
        return TextInfo{
            elements::Page::CONFIG_SETTINGS,
            elements::CharSizeType::M,
            elements::HighFix{elements::PositionType::MID, elements::coord::PLAYER_COUNT_TEXT_Y},
            "Player Count"
        };
    }

}

template<elements::TextType type>
struct elements::Info<elements::TextType, type> {
    static constexpr auto info = make_text_info<type>();

    static constexpr Page get_page() { return info.page; }
    static constexpr CharSizeType get_char_size() { return info.char_size; }
    static constexpr Position get_position() { return info.position; }
    static constexpr sf::String get_text() { return sf::String(info.text.data()); }
};

namespace elements {
    template<TextType type>
    concept text_type_trait =
        initilized_type<TextType, type> &&
        has_position<TextType, type> &&
        std::is_same_v<std::remove_cv_t<decltype(Info<TextType, type>::get_char_size())>, CharSizeType> &&
        requires{
        { Info<TextType, type>::get_text() } -> std::convertible_to<sf::String>;
        };

    template<TextType type>
    requires text_type_trait<type>
    class TextElement final : public PageElement<Info<TextType,type>::get_page()>,
                              public StaticUntouchableElement,
                              public UITracker {

        using Info = Info<TextType, type>;

    public:
        explicit TextElement(const UIManager& manager) :
        StaticUntouchableElement({
            .texture = manager.texture_manager.get_text_background_texture(
                static_cast<unsigned int>(Info::get_char_size()),
                Info::get_text().getSize()),

            .position = PositionManager::get_position(Info::get_position())}),

        UITracker(manager) {
            this->set_origin_to_centre();

            const auto char_size = Info::get_char_size();
           manager.texture_manager.draw_text(
               this->get_sprite(),
               Info::get_text(),
               static_cast<unsigned int>(char_size));
        }
    };

    using YahtzeeMainTextElement = TextElement<TextType::YahtzeeMain>;
    using ChooseGameModeTextElement = TextElement<TextType::ChooseGameMode>;
    using SettingsTextElement = TextElement<TextType::Settings>;
    using PlayerCountTextElement = TextElement<TextType::PlayerCount>;
    using DiceCountTextElement = TextElement<TextType::DiceCount>;
}


#endif //TEXTELEMENT_H
