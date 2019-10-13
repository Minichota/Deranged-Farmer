#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "renderable.hpp"
#include "event-handler.hpp"

class GameState : public Renderable, public Event_Handler
{
	public:
	GameState(SDL_Renderer* renderer);
	virtual ~GameState();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void init()   = 0;
	virtual void clear()  = 0;

	virtual void handle_event(SDL_Event event) = 0;
};
#endif
