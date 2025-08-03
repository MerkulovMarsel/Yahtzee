//
// Created by Марсель on 02.08.2025.
//

#include "ConfigException.h"


const char * ConfigException::what() const noexcept {
    switch (exceptionType) {
        case ExceptionType::INVALID_CALC_FUNCTION_TEMPLATE:
            return "Invalid calc function template";
        case ExceptionType::NO_IMPLEMENTATION_CATEGORY_CALC_FUNCTION:
            return "No category calc function implementation";
        case ExceptionType::NO_IMPLEMENTATION_BONUS_CALC_FUNCTION:
            return "No bonus calc function implementation";
        default:
            return "Unknown exception type";
    }
}
