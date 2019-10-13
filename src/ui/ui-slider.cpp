#include <iostream>

#include "ui-slider.hpp"

UI_Slider::UI_Slider(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, int min_value, int max_value, int pos_count):
UI_Base(renderer, pos, size, scale),
max_value(max_value),
min_value(min_value),
difference(max_value - min_value),
pos_count(pos_count)
{
	this->state = 0;
}

UI_Slider::~UI_Slider()
{
}

void UI_Slider::update()
{
}

// TODO use pos_count instead of every value in between
void UI_Slider::render()
{
	static const int bar_height = 30 * scale.y;
	static const int bar_width  = (size.x * scale.x / 10);
	SDL_Rect full_bar = {pos.x, pos.y, (int)(size.x * scale.x), (int)(size.y * scale.y)};
	SDL_Rect pos_bar  = {(int)(pos.x + (size.x - bar_width) * (state / (double)difference)),
						(int)(pos.y - (bar_height - size.y) / 2),
						bar_width,
						bar_height};
	SDL_RenderFillRect(renderer, &full_bar);
	SDL_RenderFillRect(renderer, &pos_bar);
}

// TODO implement mouse controlling of slider
void UI_Slider::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				// temporary, for testing
				case SDLK_UP:
				{
					state++;
				} break;
				case SDLK_DOWN:
				{
					state--;
				} break;
			}
		} break;
	}
}

int UI_Slider::get_value()
{
	return this->difference * (this->state / (double)this->difference);
}

int UI_Slider::get_state()
{
	return this->state;
}

void UI_Slider::set_state(bool state)
{
	this->state = state;
}
