// GameException.h
// Created by Марсель on 31.07.2025.

#ifndef GAMEEXCEPTION_H
#define GAMEEXCEPTION_H

#include "exception/YahtzeeException.h"
#include <string>

class GameException final : public YahtzeeException {
public:
    explicit GameException(const std::string& message = "Game error occurred")
        : YahtzeeException(message) {}

    ~GameException() override = default;

};

#endif // GAMEEXCEPTION_H