#include <iostream>

#include "ui-slider.hpp"

UI_Slider::UI_Slider(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, int min_value, int max_value, int pos_count):
UI_Base(renderer, pos, size, scale),
max_value(max_value),
min_value(min_value),
difference(max_value - min_value),
pos_fraction(size.x / pos_count),
pos_count(pos_count)
{
	this->state = 0;
	this->mouse_down = false;
}

UI_Slider::~UI_Slider()
{
}

void UI_Slider::update()
{
}

void UI_Slider::render()
{
	static const int bar_height = 30 * scale.y;
	static const int bar_width  = 10 * scale.x;
	SDL_Rect full_bar = {pos.x, pos.y, (int)(size.x * scale.x), (int)(size.y * scale.y)};
	SDL_Rect pos_bar  = {(int)(pos.x + (size.x - bar_width) * state * difference / pos_count / difference),
						(int)(pos.y - (bar_height - size.y) / 2),
						bar_width,
						bar_height};
	SDL_RenderFillRect(renderer, &full_bar);
	SDL_RenderFillRect(renderer, &pos_bar);
}

void UI_Slider::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			if(in_bounds(Ivec(event.button.x, event.button.y)))
			{
				mouse_down = true;
				set_state(get_closest_tick(Ivec(event.button.x, event.button.y)));
			}
		} break;
		case SDL_MOUSEBUTTONUP:
		{
			mouse_down = false;
		} break;
		case SDL_MOUSEMOTION:
		{
			if(mouse_down)
			{
				set_state(get_closest_tick(Ivec(event.motion.x, event.motion.y)));
			}
		} break;
	}
}

int UI_Slider::get_closest_tick(Ivec click_pos)
{
	int dx = click_pos.x - this->pos.x;
	if(dx > size.x)
	{
		return this->pos_count;
	}
	else if(dx < min_value)
	{
		return 0;
	}
	else
	{
		return std::round(dx / (double)pos_fraction);
	}
}

int UI_Slider::get_value()
{
	return this->difference * (this->state * (this->difference / (double)this->pos_count) / this->difference);
}

int UI_Slider::get_state()
{
	return this->state;
}

void UI_Slider::set_state(int state)
{
	this->state = state;
}
