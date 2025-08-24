//
// Created by Марсель on 23.08.2025.
//

#ifndef DATA_H
#define DATA_H
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>

#include "Constant.h"
#include "ElementsTypes.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/System/Vector2.hpp"

namespace elements {
    static constexpr std::uint8_t create_pos_cord(std::uint8_t x, std::uint8_t y) {
        return x + y * 4U;
    }
    enum class PositionType : std::uint8_t {
        MID = create_pos_cord(2, 2),
        LEFT = create_pos_cord(1, 2),
        RIGHT = create_pos_cord(3, 2),
        UP = create_pos_cord(2, 1),
        DOWN = create_pos_cord(2, 3),
        UP_LEFT = create_pos_cord(1,1),
        UP_RIGHT = create_pos_cord(3,1),
        DOWN_LEFT = create_pos_cord(1,3),
        DOWN_RIGHT = create_pos_cord(3,3),
    };

    enum class CharSizeType : std::uint8_t {
        XXL = 200U,
        XL = 100U,
        L = 50U,
        M = 40,
        S = 30,
        XS = 20,
        XXS = 10
    };

    using HighFix = std::pair<PositionType, float>;
    using Cord = sf::Vector2f;
    using Color = sf::Color;
    using Position = std::variant<PositionType, Cord, HighFix>;


    struct Info {
        virtual ~Info() = default;
        Info() = default;
    };
    class TypeData {
    public:
        virtual ~TypeData() = default;

        [[nodiscard]] virtual Position get_position(Code) const noexcept = 0;

        [[nodiscard]] virtual const Info* get_info(Code) const noexcept = 0;
    };
    template <typename T>
    using Storage = std::unordered_map<Code, std::pair<Position, T>>;


    struct TextInfo final : Info {
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
            }
        }) {}

        [[nodiscard]] Position get_position(const Code code) const noexcept override {
            return texts.at(code).first;
        }

        [[nodiscard]] const Info* get_info(const Code code) const noexcept override {
            return &texts.at(code).second;
        }
    };


    struct SliderInfo final : Info {
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

        [[nodiscard]] const Info* get_info(const Code code) const noexcept override {
            return &sliders.at(code).second;
        }
    };


    class Data {
        TextData text_data;
        SliderData slider_data;
        std::unordered_map<Code, TypeData*> data {
            {TEXT_TYPE_ID, &text_data},
            {SLIDER_TYPE_ID, &slider_data}
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


        template<ElementType Type, typename InfoType, typename DataType>
        [[nodiscard]] const InfoType* get_info(Type type) const {
            const Code type_code = GET_TYPE_ID(type);
            const auto it = data.find(type_code);
            if (it == data.end()) {
                throw std::invalid_argument("Invalid type for get_info");
            }
            const auto* const ptr = dynamic_cast<DataType*>(it->second);
            if (ptr == nullptr) {
                throw std::invalid_argument("Invalid type for get_info");
            }
            const auto* info = dynamic_cast<const InfoType*>(ptr->get_info(GET_VALUE(type)));
            if (info == nullptr) {
                throw std::invalid_argument("Invalid type for get_info");
            }
            return info;
        }
    };
}



#endif //DATA_H
