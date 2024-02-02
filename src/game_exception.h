#pragma once
#include <exception>
#include <iostream>

class game_exception : public std::exception
{
public:
	const char* message;

	game_exception(const char* message) : message(message) {}

	const char* what() const noexcept override
	{
		return message;
	}
};