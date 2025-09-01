//
// Created by Марсель on 23.08.2025.
//

#ifndef DATA_H
#define DATA_H
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <variant>

#include "Constant.hpp"
#include "ElementsTypes.hpp"

#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

namespace elements {
    static constexpr std::uint8_t grid_size = 8;

    static constexpr std::uint8_t create_coord(const std::uint8_t x, const std::uint8_t y) {
        if (x >= grid_size || y >= grid_size) {
            throw std::out_of_range("grid size out of range");
        }
        return x + (y * grid_size);
    }

    enum class PositionType : std::uint8_t {
        MID                 = create_coord(grid_size / 2,     grid_size / 2),
        LEFT                = create_coord(grid_size / 4,     grid_size / 2),
        LEFT_MID            = create_coord(grid_size * 3 / 8, grid_size / 2),
        RIGHT               = create_coord(grid_size * 3 / 4, grid_size / 2),
        RIGHT_MID           = create_coord(grid_size * 5 / 8, grid_size / 2),
        UP                  = create_coord(grid_size / 2,     grid_size / 4),
        DOWN                = create_coord(grid_size / 2,     grid_size * 3 / 4),
        UP_LEFT             = create_coord(grid_size / 4,     grid_size / 4),
        UP_RIGHT            = create_coord(grid_size * 3 / 4, grid_size / 4),
        DOWN_LEFT           = create_coord(grid_size / 4,     grid_size * 3 / 4),
        DOWN_LEFT_MID       = create_coord(grid_size * 3 / 8, grid_size * 3 / 4),
        DOWN_LEFT_LEFT      = create_coord(grid_size * 1 / 8, grid_size * 3 / 4),
        DOWN_RIGHT          = create_coord(grid_size * 3 / 4, grid_size * 3 / 4),
        DOWN_RIGHT_MID      = create_coord(grid_size * 5 / 8, grid_size * 3 / 4),
        DOWN_RIGHT_RIGHT    =create_coord(grid_size * 7 / 8,  grid_size * 3 / 4),
    };

    static constexpr sf::Vector2f get_normalized_coord(PositionType pos) {
        const auto value = static_cast<std::uint8_t>(pos);
        const std::uint8_t x = value % grid_size;
        const std::uint8_t y = value / grid_size;
        static constexpr auto edge = 0.05f;
        return {
            (static_cast<float>(x) / grid_size),
            (static_cast<float>(y) / grid_size)
        };
    }

    enum class CharSizeType : std::uint8_t {
        XXL = 200U,
        XL = 100U,
        L = 70U,
        M = 40,
        S = 30,
        XS = 25,
        XXS = 20
    };

    using HighFix = std::pair<PositionType, float>;
    using Cord = sf::Vector2f;
    using Color = sf::Color;
    using Position = std::variant<PositionType, Cord, HighFix>;
}



namespace elements {
    template<typename Type, Type>
    struct Info {
        using ErrorUninitializedType = bool;
    };

    template<typename T>
    concept has_page_access = requires(T t) {
        requires std::same_as<std::remove_cvref_t<decltype(t.page)>, Page>;
    } || requires(T t) {
        requires std::same_as<std::remove_cvref_t<decltype(t.get_page())>, Page>;
        { t.get_page() } -> std::same_as<Page>;
    };


    template<typename Type, Type type>
    concept initilized_type = has_page_access<Info<Type, type>> && requires {
        requires !requires { typename Info<Type, type>::ErrorUninitializedType; };
    };

    template<typename Type, Type type>
    concept has_position = requires
    {
        {Info<Type,type>::get_position()} -> std::same_as<Position>;
    };

    template<typename Type, Type type>
    concept has_state = requires {typename Info<Type,type>::State; };
}


template<>
struct elements::Info<elements::SlidersType, elements::SlidersType::DiceCountSlider> {
    using State = std::size_t;
    static constexpr auto page = Page::CONFIG_SETTINGS;

};


namespace elements{
    struct InfoBase {
        virtual ~InfoBase() = default;
        InfoBase() = default;
    };
    class TypeData {
    public:
        virtual ~TypeData() = default;

        [[nodiscard]] virtual Position get_position(Code) const noexcept = 0;

        [[nodiscard]] virtual const InfoBase* get_info(Code) const noexcept = 0;
    };
    template <typename T>
    using Storage = std::unordered_map<Code, std::pair<Position, T>>;


    struct TextInfo final : InfoBase {
        TextInfo(std::string  text, const CharSizeType char_size) : text(std::move(text)), char_size(char_size) {}
        std::string text;
        CharSizeType char_size;
    };
    class TextData final : public TypeData {
        Storage<TextInfo> texts;
    public:
        TextData() : texts({
            {GET_VALUE(TextType::YahtzeeMain),
                {PositionType::UP, TextInfo{"Yahtzee", CharSizeType::XXL}}
            },
            {GET_VALUE(TextType::ChooseGameMode),
                {PositionType::MID, TextInfo{"Choose game mode:", CharSizeType::XL}}
            },
            {GET_VALUE(TextType::Settings),
                {HighFix{PositionType::MID, coord::SETTINGS_TEXT_Y}, TextInfo{"Settings", CharSizeType::L}}
            },
            {GET_VALUE(TextType::PlayerCount),
                {HighFix{PositionType::MID, coord::PLAYER_COUNT_TEXT_Y}, TextInfo{"Player count", CharSizeType::M}}
            },
            {GET_VALUE(TextType::DiceCount),
                {HighFix{PositionType::MID, coord::DICE_COUNT_TEXT_Y}, TextInfo{"Dice count", CharSizeType::M}}
            },
        }) {}

        [[nodiscard]] Position get_position(const Code code) const noexcept override {
            return texts.at(code).first;
        }

        [[nodiscard]] const InfoBase* get_info(const Code code) const noexcept override {
            return &texts.at(code).second;
        }
    };


    struct SliderInfo final : InfoBase {
        SliderInfo(const std::size_t min, const std::size_t max, const std::size_t step, const CharSizeType size)
        : value_min(min), value_max(max), value_step(step), char_size(size) {}
        std::size_t value_min;
        std::size_t value_max;
        std::size_t value_step;
        CharSizeType char_size;
    };
    class SliderData final : public TypeData {
        Storage<SliderInfo> sliders;
    public:
        SliderData() : sliders({
            {GET_VALUE(SlidersType::DiceCountSlider),
                {Position{HighFix{PositionType::MID, coord::SLIDER_DICE_COUNT_X}},
                 SliderInfo{3U, 7U, 1U, CharSizeType::XS}}
            }
        }) {}

        [[nodiscard]] Position get_position(const Code code) const noexcept override {
            return sliders.at(code).first;
        }

        [[nodiscard]] const InfoBase* get_info(const Code code) const noexcept override {
            return &sliders.at(code).second;
        }
    };


    struct PlayerCountInfo final : InfoBase {
        PlayerCountInfo(std::string&& text, const std::size_t player_count) : text(std::move(text)), player_count(player_count) {}
        static constexpr auto char_size = CharSizeType::M;
        std::string text;
        std::size_t player_count;
    };
    class PlayerCountData final : public TypeData {
        Storage<PlayerCountInfo> players;
    public:
        PlayerCountData() : players({
            {GET_VALUE(PlayerCountButtonType::Single),
                {HighFix(PositionType::LEFT, coord::PLAYER_COUNT_BUTTON_Y),
                    PlayerCountInfo{"Single", 1U}}
                },
                {GET_VALUE(PlayerCountButtonType::OneVsOne),
                {HighFix(PositionType::RIGHT, coord::PLAYER_COUNT_BUTTON_Y),
                     PlayerCountInfo{"1 VS 1", 2U}}
                }
        }) {}

        [[nodiscard]] Position get_position(const Code code) const noexcept override {
            return players.at(code).first;
        }

        [[nodiscard]] const InfoBase * get_info(const Code code) const noexcept override {
            return &players.at(code).second;
        }
    };


    struct ScreenInfo final : InfoBase {
        explicit ScreenInfo(const CharSizeType char_size) :
        char_size(char_size) {}

        CharSizeType char_size;
    };

    class ScreenData final : public TypeData {
        Storage<ScreenInfo> screens;
    public:
        ScreenData() : screens({
            {GET_VALUE(ScreenType::RollCountScreen),
                {HighFix{PositionType::MID, coord::ROLL_COUNT_SCREEN_Y},
                    ScreenInfo{CharSizeType::S}}}
        }) {}
        [[nodiscard]] Position get_position(const Code code) const noexcept override {
            return screens.at(code).first;
        }

        [[nodiscard]] const InfoBase* get_info(const Code code) const noexcept override {
            return &screens.at(code).second;
        }
    };

    class Data {
        TextData text_data;
        SliderData slider_data;
        PlayerCountData player_count_button_data;
        ScreenData screen_info;
        std::unordered_map<Code, TypeData*> data {
            {TEXT_TYPE_ID, &text_data},
            {SLIDER_TYPE_ID, &slider_data},
            {PLAYER_COUNT_BUTTON_ID, &player_count_button_data},
            {SCREEN_TYPE_ID, &screen_info}
        };

    public:
        template<ElementType Type>
        [[nodiscard]] Position get_position(Type type) const {
            const Code type_code = GET_TYPE_ID(type);
            const auto it = data.find(type_code);
            if (it == data.end()) {
                throw std::invalid_argument("Invalid type for get_position");
            }
            return it->second->get_position(GET_VALUE(type));
        }


        template<typename Key>
        [[nodiscard]] const typename Key::InfoType* get_info(typename Key::Type type) const {
            const Code type_code = GET_TYPE_ID(type);
            const auto it = data.find(type_code);
            if (it == data.end()) {
                throw std::invalid_argument("Invalid type for get_info");
            }
            const auto* const ptr = dynamic_cast<typename Key::DataType*>(it->second);
            if (ptr == nullptr) {
                throw std::invalid_argument("Invalid type for get_info");
            }
            const auto* info = dynamic_cast<const typename Key::InfoType*>(ptr->get_info(GET_VALUE(type)));
            if (info == nullptr) {
                throw std::invalid_argument("Invalid type for get_info");
            }
            return info;
        }
    };
}



#endif //DATA_H
