#include <SDL2/SDL.h>
#include <iostream>

#include "console-log.hpp"

Console_Log::Console_Log(std::string text, long long life_time)
{
	this->text = text;
	this->life_time = life_time;
	this->spawn_time = SDL_GetTicks();
}

Console_Log::~Console_Log()
{
}

bool Console_Log::get_active()
{
	long long curr_time = SDL_GetTicks();
	return (curr_time - spawn_time < life_time);
}

std::string& Console_Log::get_text()
{
	return this->text;
}
