//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <functional>
#include <numeric>
#include <ranges>
#include <vector>

#include "exception/config/ConfigException.h"


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
    using Dices = std::vector<std::pair<DiceValues, bool>>;

    static constexpr std::size_t to_n(const DiceValues dice) {
        return static_cast<std::size_t>(dice);
    }

    using ScoreType = std::int64_t;


    enum class AvailableCategory : std::uint8_t {
        // Simple for start
        SUM_1,SUM_2,SUM_3,SUM_4,SUM_5,SUM_6,
    };

    using CategoryCalcFunction = std::function<ScoreType(Dices)>;


    static CategoryCalcFunction make_sum_function(DiceValues target) {
        return [target](Dices dices) {
            return std::accumulate(dices.begin(), dices.end(), ScoreType{0},
                [target](ScoreType sum, auto val) {
                    return sum + (val == target ? to_n(target) : 0);
                });
        };
    }

    static CategoryCalcFunction get_calc_function(const AvailableCategory category) {
        switch (category) {
            case AvailableCategory::SUM_1:
            case AvailableCategory::SUM_2:
            case AvailableCategory::SUM_3:
            case AvailableCategory::SUM_4:
            case AvailableCategory::SUM_5:
            case AvailableCategory::SUM_6:
                return make_sum_function(static_cast<DiceValues>(category));
            default:
                throw
                ConfigException(ConfigException::ExceptionType::NO_IMPLEMENTATION_CATEGORY_CALC_FUNCTION);
        }
    }

    struct Category {
        CategoryCalcFunction calc;
        AvailableCategory type;
        std::optional<ScoreType> value;

        explicit Category(const AvailableCategory category) :
            calc(get_calc_function(category)),
            type(category)
        {}

        ScoreType operator()(const Dices& dices) const {
            return calc(dices);
        }
    };

    using Categories = std::vector<Category>;

    using BonusCalcFunction = std::function<ScoreType(const Categories&)>;


    enum class AvailableBonusCalcFUnction : std::uint8_t {
        CLASSIC_BONUS_63 = 63
    };

    static constexpr std::size_t to_n(const AvailableBonusCalcFUnction dice) {
        return static_cast<std::size_t>(dice);
    }


    static ScoreType classic_border_bonus(const Categories& categories) {
        ScoreType result = 0;
        for (const auto& c : categories) {
            if (c.value &&
                (c.type == AvailableCategory::SUM_1 ||
                 c.type == AvailableCategory::SUM_2 ||
                 c.type == AvailableCategory::SUM_3 ||
                 c.type == AvailableCategory::SUM_4 ||
                 c.type == AvailableCategory::SUM_5 ||
                 c.type == AvailableCategory::SUM_6)) {
                result += c.value.value();
            }
        }
        return result;
    }

    static BonusCalcFunction get_bonus_function(const AvailableBonusCalcFUnction bonus) {
        switch (bonus) {
            case AvailableBonusCalcFUnction::CLASSIC_BONUS_63:
                return classic_border_bonus;
            default:
                throw ConfigException(ConfigException::ExceptionType::NO_IMPLEMENTATION_BONUS_CALC_FUNCTION);
        }
    }

    struct Bonus {
        BonusCalcFunction calc_score;
        ScoreType bonus;
        ScoreType threshold;
    };


    enum class GameRuleFlags : std::uint32_t {
        ASYNC_MODE = 0x01,
        OVERRIDE_CATEGORY = 0x02,
    };


    bool is_rule_enabled(const GameRuleFlags rule) const {
        return (enabled_rules & static_cast<uint32_t>(rule)) != 0u;
    }

    std::size_t players_count;
    std::size_t dice_count;
    std::size_t category_count;
    std::size_t bonus_count;
    std::size_t rolls_count;
    uint32_t enabled_rules = 0;
    std::vector<Categories> categories;
    std::vector<Bonus> bonus;

    enum SpecialEvent : std::uint8_t {
        STOP_PLAYING_EVENT
    };
};

#endif //GAMECONFIG_H
