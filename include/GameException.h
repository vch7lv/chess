#pragma once
#include <exception>
#include <string>

class GameException : public std::exception
{

    std::string message;
    const char* what() const noexcept override;

    public:
        GameException(const std::string& message);
};