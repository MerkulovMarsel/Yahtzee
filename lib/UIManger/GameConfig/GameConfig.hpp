//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <cstddef>
#include <cstdint>
#include <functional>
#include <numeric>
#include <optional>
#include <ranges>
#include <utility>
#include <vector>

#include "exception/config/ConfigException.hpp"


struct GameConfig {
    enum class DiceValues : std::uint8_t {
        UNKNOW = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6
    };

    using DiceState = std::pair<DiceValues, bool>;

    using Dices = std::vector<DiceState>;

    static constexpr std::size_t to_n(const DiceValues dice) {
        return static_cast<std::size_t>(dice);
    }

    using ScoreType = std::int64_t;


    enum class AvailableCategory : std::uint8_t {
        SUM_1,SUM_2,SUM_3,SUM_4,SUM_5,SUM_6,
    };

    using CategoryCalcFunction = std::function<ScoreType(Dices)>;


    template<DiceValues target>
    static constexpr CategoryCalcFunction make_sum_function() {
        return [](Dices dices) {
            return std::accumulate(dices.begin(), dices.end(), ScoreType{0},
                [](ScoreType sum, auto val) {
                    return sum + (val.first == target ? to_n(target) : 0);
                });
        };
    }

    template<AvailableCategory category>
    static constexpr CategoryCalcFunction get_calc_function() {
        switch (category) {
            case AvailableCategory::SUM_1:
            case AvailableCategory::SUM_2:
            case AvailableCategory::SUM_3:
            case AvailableCategory::SUM_4:
            case AvailableCategory::SUM_5:
            case AvailableCategory::SUM_6:
                return make_sum_function<static_cast<DiceValues>(category)>();
            default:
                throw
                ConfigException(ConfigException::ExceptionType::NO_IMPLEMENTATION_CATEGORY_CALC_FUNCTION);
        }
    }

    template<AvailableCategory category>
    static constexpr bool is_classic_category() {
        switch (category) {
            default:
                return true;
        }
    }

    class CategoryBase {
        std::optional<ScoreType> value ;
    public:
        virtual ~CategoryBase() = default;

        virtual ScoreType operator()(const Dices& dices) const = 0;

        std::optional<ScoreType> get_value() const noexcept {
            return value ;
        }

        void fix(const Dices& dices) noexcept {
            value = this->operator()(dices) ;
        }
    };

    template<AvailableCategory category>
    struct Category final : CategoryBase {

        static constexpr CategoryCalcFunction calc = get_calc_function<category>();
        std::optional<ScoreType> value = std::nullopt;
        bool enabled = is_classic_category<category>();

        ScoreType operator()(const Dices& dices) const override {
            return calc(dices);
        }
    };

    using CategoryState = std::pair<AvailableCategory, bool>;
    using Categories = std::vector<std::pair<std::optional<ScoreType>, AvailableCategory>>;

    using BonusCalcFunction = std::function<ScoreType(const Categories&)>;


    enum class AvailableBonus : std::uint8_t {
        CLASSIC_BONUS_63 = 63
    };

    static constexpr std::size_t to_n(const AvailableBonus dice) {
        return static_cast<std::size_t>(dice);
    }


    static ScoreType classic_border_bonus(const Categories& categories) {
        ScoreType result = 0;
        for (const auto& [value,c] : categories) {
            if (value &&
                (c == AvailableCategory::SUM_1 ||
                 c == AvailableCategory::SUM_2 ||
                 c == AvailableCategory::SUM_3 ||
                 c == AvailableCategory::SUM_4 ||
                 c == AvailableCategory::SUM_5 ||
                 c == AvailableCategory::SUM_6)) {
                result += value.value();
            }
        }
        return result;
    }

    static BonusCalcFunction get_bonus_function(const AvailableBonus bonus) {
        switch (bonus) {
            case AvailableBonus::CLASSIC_BONUS_63:
                return classic_border_bonus;
            default:
                throw ConfigException(ConfigException::ExceptionType::NO_IMPLEMENTATION_BONUS_CALC_FUNCTION);
        }
    }

    struct BonusState {
        BonusCalcFunction calc_score;
        ScoreType bonus;
        ScoreType threshold;
        bool enabled;

        BonusState() {

        }
    };

    using Bonuses = std::vector<AvailableBonus>;

    enum class GameRuleFlags : std::uint32_t {
        ASYNC_MODE = 0x01,
        OVERRIDE_CATEGORY = 0x02,
    };


    bool is_rule_enabled(const GameRuleFlags rule) const {
        return (game_state.enabled_rules & static_cast<std::uint32_t>(rule)) != 0u;
    }

    struct GameState {
        using RollCountType = std::pair<std::optional<std::size_t>, bool>;
        Categories categories;
        Bonuses bonus;
        RollCountType roll_count = {3, true};
        std::size_t players_count =  1;
        std::size_t dice_count = 5;
        std::size_t category_count = 0;
        std::size_t bonus_count = 0;
        uint32_t enabled_rules = 0;
    };

    GameState game_state;


    enum SpecialEvent : std::uint8_t {
        STOP_PLAYING_EVENT
    };

};

#endif //GAMECONFIG_H
