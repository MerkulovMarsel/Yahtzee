//
// Created by Марсель on 19.08.2025.
//

#ifndef ELEMENTSTYPES_H
#define ELEMENTSTYPES_H
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

#include "SFML/Graphics/Color.hpp"

namespace elements {
    enum class Page : std::uint8_t {
        START_SETTING   = 1,
        CONFIG_SETTINGS = 0,
        GAME_PLAYING    = 2,
        GAME_OVER       = 3
    };

    enum class GameMode : std::uint8_t {
        CLASSIC,
        COUNT_DOWN,
        RACE,
        SPEED,
        TEST
    };

    enum class PlayerCount : std::uint8_t {
        SINGLE = 1,
        ONE_VS_ONE = 2
    };

    using Code = std::uint16_t;
    static constexpr Code LEVEL = 1U << 8U;
    static constexpr Code TYPE_MASK = 0xFF00U;
    static constexpr Code VALUE_MASK = 0x00FFU;

    template <typename Enum>
    constexpr Code NEXT(Enum type) {
        return static_cast<Code>(type) + 1U;
    }
    template <typename Enum>
    constexpr Code NEXT_SET(Enum type, const Code value) {
        return static_cast<Code>(type) + value;
    }
    template <typename Enum>
    constexpr Code NEXT_TYPE(Enum type) {
        return (static_cast<Code>(type) & TYPE_MASK) + LEVEL;
    }
    template <typename Enum>
    constexpr Code GET_TYPE_ID(Enum type) {
        return (static_cast<Code>(type) & TYPE_MASK) >> 8U;
    }
    template <typename Enum>
    constexpr Code GET_VALUE(Enum type) {
        return static_cast<Code>(type) & VALUE_MASK;
    }

    enum class TextType : Code {
        YahtzeeMain =  0U,
        ChooseGameMode = NEXT(YahtzeeMain)
    };
    static constexpr Code TEXT_TYPE_ID = GET_TYPE_ID(TextType::YahtzeeMain);
    template<TextType type>
    static constexpr Page get_text_page() {
        switch (type) {
            case TextType::YahtzeeMain:
            case TextType::ChooseGameMode:
                return Page::START_SETTING;
        }
        std::unreachable();
    }

    enum class PlayerCountButtonType : Code {
        Single = NEXT_TYPE(TextType::YahtzeeMain),
        OneVsOne = NEXT(Single)
    };
    static constexpr Code PLAYER_COUNT_BUTTON_ID = GET_TYPE_ID(PlayerCountButtonType::Single);

    enum class SlidersType : Code {
        DiceCountSlider = NEXT_TYPE(PlayerCountButtonType::Single)
    };
    static constexpr Code SLIDER_TYPE_ID = GET_TYPE_ID(SlidersType::DiceCountSlider);

    template<typename T>
    concept ElementType = std::is_enum_v<T> && (
                std::is_same_v<T, SlidersType> ||
                std::is_same_v<T, TextType> );
}

namespace elements {
    static constexpr std::size_t MODE_COUNT = 5;

    static constexpr std::size_t MAX_COUNT_DICE = 7ULL;
    static constexpr std::size_t MIN_COUNT_DICE = 3ULL;
    static constexpr std::size_t MAX_COUNT_CATEGORY = 6ULL;

    inline const sf::Color TOUCH_COLOR = sf::Color::Yellow;
    inline const sf::Color NORMAL_COLOR = sf::Color::White;
    inline const sf::Color TEXT_COLOR = sf::Color::White;
}


#endif //ELEMENTSTYPES_H
