#ifndef UI_SWITCH_HPP
#define UI_SWITCH_HPP

#include "event-handler.hpp"
#include "ui-base.hpp"

class UI_Switch : public UI_Base, public Event_Handler
{
	public:
	UI_Switch(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color color = {});
	~UI_Switch();

	void update();
	void render();

	void handle_event(SDL_Event event);

	bool is_on();

	private:
	bool toggle;
};
#endif
