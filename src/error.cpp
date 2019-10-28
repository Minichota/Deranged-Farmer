#include <iostream>
#include <cstring>

#include "error.hpp"
#include "game.hpp"

Error::Error(bool condition, std::vector<const char*> message, bool game_ending)
{
	this->condition = condition;
	this->message = message;
	this->game_ending = game_ending;
}

Error::~Error()
{
	if(condition)
	{
		for(const char* i : message)
		{
			std::cout << i;
		}
		std::cout << std::endl;
		message.clear();
		if(game_ending)
		{
			Game::close();
		}
	}
}
