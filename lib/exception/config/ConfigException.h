//
// Created by Марсель on 02.08.2025.
//

#ifndef CONFIGEXCEPTION_H
#define CONFIGEXCEPTION_H
#include "exception/YahtzeeException.h"


class ConfigException final : YahtzeeException {
public:
    enum class ExceptionType {
        INVALID_CALC_FUNCTION_TEMPLATE,
        NO_IMPLEMENTATION_CATEGORY_CALC_FUNCTION,
    };

    explicit ConfigException(const ExceptionType type) : exceptionType(type) {}

    const char* what() const noexcept override ;

private:
    ExceptionType exceptionType;
};



#endif //CONFIGEXCEPTION_H
