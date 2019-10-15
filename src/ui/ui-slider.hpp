#ifndef UI_SLIDER_HPP
#define UI_SLIDER_HPP

#include "event-handler.hpp"
#include "ui-base.hpp"

class UI_Slider : public UI_Base, public Event_Handler
{
	public:
	UI_Slider(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, int min_value, int max_value, int pos_count = 2);
	~UI_Slider();

	void update();
	void render();

	void handle_event(SDL_Event event);

	int get_closest_tick(Ivec pos);

	int get_value();

	int get_state();
	void set_state(int state);

	private:
	int state;
	const int max_value;
	const int min_value;
	const int difference;
	const double pos_fraction;
	const int pos_count;

	bool mouse_down;

	bool in_bounds(Ivec point);
};
#endif
