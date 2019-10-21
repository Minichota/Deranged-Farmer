#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "renderable.hpp"
#include "event-handler.hpp"

class Game_State : public Renderable, public Event_Handler
{
	public:
	Game_State(SDL_Renderer* renderer);
	virtual ~Game_State();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void init()   = 0;
	virtual void clear()  = 0;

	virtual void handle_event(SDL_Event event) = 0;
};
#endif
