#ifndef UI_SLIDER_HPP
#define UI_SLIDER_HPP

#include "event-handler.hpp"
#include "ui-base.hpp"

class UI_Slider : public UI_Base, public Event_Handler
{
	public:
	UI_Slider(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale,
			  int min_value, int max_value, int pos_count = 2,
			  SDL_Color bar_color = {}, SDL_Color slider_color = {});
	~UI_Slider();

	void update();
	void render();

	void handle_event(const SDL_Event& event);

	int get_closest_tick(Ivec pos);

	int get_value();

	int get_state();
	void set_state(int state);

	void set_bind(int* binded_value);

	private:
	SDL_Color slider_color;

	int state;
	const int max_value;
	const int min_value;
	const int difference;
	const double pos_fraction;
	const int pos_count;

	int* binded_value = nullptr;

	bool mouse_down;

	bool in_bounds(Ivec point);
};
#endif
