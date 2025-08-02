//
// Created by Марсель on 29.07.2025.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <functional>
#include <span>

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
    using Dices = std::span<DiceValues>;

    static constexpr std::size_t to_n(const DiceValues dice) {
        return static_cast<std::size_t>(dice);
    }

    using ScoreType = std::int64_t;


    enum class AvailableCategory : std::uint8_t {
        // Simple for start
        SUM_1,SUM_2,SUM_3,SUM_4,SUM_5,SUM_6,
    };

    using CategoryCalcFunction = std::function<ScoreType(Dices)>;

    template<std::size_t N>
    static ScoreType ctor_sumN(const Dices dices) {
        if constexpr (N <= to_n(DiceValues::UNKNOW) || N > to_n(DiceValues::SIX)) {
            throw ConfigException(ConfigException::ExceptionType::INVALID_CALC_FUNCTION_TEMPLATE);
        }
        ScoreType result = 0;
        for (const auto& d : dices) {
            result += (d == static_cast<DiceValues>(N)) ? N : 0;
        }
        return result;
    }

    static CategoryCalcFunction get_calc_function(const AvailableCategory category) {
        switch (category) {
            case AvailableCategory::SUM_1:
                return ctor_sumN<to_n(DiceValues::ONE)>;
            case AvailableCategory::SUM_2:
                return ctor_sumN<to_n(DiceValues::TWO)>;
            case AvailableCategory::SUM_3:
                return ctor_sumN<to_n(DiceValues::THREE)>;
            case AvailableCategory::SUM_4:
                return ctor_sumN<to_n(DiceValues::FOUR)>;
            case AvailableCategory::SUM_5:
                return ctor_sumN<to_n(DiceValues::FIVE)>;
            case AvailableCategory::SUM_6:
                return ctor_sumN<to_n(DiceValues::SIX)>;
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

    using Categories = std::span<Category>;

    using BonusCalcFunction = std::function<ScoreType(const Categories&)>;

    enum class AvailableBonusCalcFUnction : std::uint8_t {
        CLASSIC_BONUS_63 = 63
    };

    static constexpr std::size_t to_n(const AvailableBonusCalcFUnction dice) {
        return static_cast<std::size_t>(dice);
    }

    template<std::size_t BORDER>
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
                return classic_border_bonus<to_n(AvailableBonusCalcFUnction::CLASSIC_BONUS_63)>;
            default:
                throw ConfigException(ConfigException::ExceptionType::NO_IMPLEMENTATION_BONUS_CALC_FUNCTION);
        }
    }

    struct Bonus {
        std::function<ScoreType(const Categories&)> calc_score;
        ScoreType bonus;
        ScoreType border;
    };


    enum class Rules : std::uint8_t {
        ASINC_MODE
    };


    std::size_t dice_count;
    std::size_t category_count;
    std::size_t bonus_count;
    std::vector<Categories> categories;
    std::vector<Bonus> bonus;
    std::vector<Rules> rules;
};

#endif //GAMECONFIG_H
