//
// Created by Марсель on 31.07.2025.
//

#ifndef YAHTZEEEXCEPTION_H
#define YAHTZEEEXCEPTION_H
#include <exception>
#include <bits/basic_string.h>


class YahtzeeException : std::exception {
    YahtzeeException() = default;

    explicit YahtzeeException(const std::string & string);
};



#endif //YAHTZEEEXCEPTION_H
