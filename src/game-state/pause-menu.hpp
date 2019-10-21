#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include <vector>

#include "game-state.hpp"
#include "ui-base.hpp"

class Pause_Menu : public Game_State
{
	public:
	Pause_Menu(SDL_Renderer* renderer);
	~Pause_Menu();

	void update();
	void render();

	void init();
	void clear();

	void handle_event(SDL_Event event);

	void push_element(UI_Base* element);
	UI_Base* get_element();

	private:
	std::vector<UI_Base*> elements;
};

#endif
