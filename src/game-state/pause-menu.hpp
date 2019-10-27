#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <vector>

#include "game-state.hpp"
#include "ui-base.hpp"

class Pause_Menu : public Game_State
{
	public:
	Pause_Menu(SDL_Renderer* renderer);

	void init();

	void handle_event(SDL_Event event);
};

void quit();

#endif
