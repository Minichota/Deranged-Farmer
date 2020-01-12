#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>

#include "event-handler.hpp"
#include "renderable.hpp"
#include "ui-base.hpp"

class Game_State : public Renderable, public Event_Handler
{
	public:
	Game_State(SDL_Renderer* renderer);
	virtual ~Game_State();

	virtual void update();
	virtual void render();

	virtual void init() = 0;
	virtual void clear();

	virtual void handle_event(const SDL_Event& event);

	void push_element(UI_Base* element);
	UI_Base* get_element(size_t index);

	protected:
	std::vector<UI_Base*> elements;
};
#endif
