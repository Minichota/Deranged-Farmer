#include <iostream>
#include <cmath>
#include <cassert>

#include "ui-slider.hpp"

UI_Slider::UI_Slider(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, int min_value, int max_value, int pos_count, SDL_Color bar_color, SDL_Color slider_color):
UI_Base(renderer, pos, size, scale, bar_color),
max_value(max_value),
min_value(min_value),
difference(max_value - min_value),
pos_fraction(size.x / pos_count),
pos_count(pos_count)
{
	assert(pos_count <= size.x - 10 * scale.x);
	this->state = 0;
	this->mouse_down = false;
	this->slider_color = slider_color;
}

UI_Slider::~UI_Slider()
{
}

void UI_Slider::update()
{
	if(binded_value != nullptr)
	{
		*binded_value = get_value();
	}
}

void UI_Slider::render()
{
	const int bar_height = 30 * scale.y;
	const int bar_width  = 10 * scale.x;
	SDL_Rect full_bar = {get_pos().x,
						get_pos().y,
						(int)std::round(size.x * scale.x),
						(int)std::round(size.y * scale.y)};
	SDL_Rect pos_bar  = {(int)std::round(get_pos().x + (size.x - bar_width) * state / pos_count),
						(int)std::round(get_pos().y - (bar_height - size.y) / 2),
						bar_width,
						bar_height};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(renderer, &full_bar);
	SDL_SetRenderDrawColor(renderer, slider_color.r, slider_color.g, slider_color.b, slider_color.a);
	SDL_RenderFillRect(renderer, &pos_bar);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
				set_state(get_closest_tick(Ivec(event.button.x - 5 * scale.x, event.button.y)));
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
				set_state(get_closest_tick(Ivec(event.motion.x - 5 * scale.x, event.motion.y)));
			}
		} break;
	}
}

int UI_Slider::get_closest_tick(Ivec click_pos)
{
	int dx = click_pos.x - this->get_pos().x;
	if(dx > size.x - 10 * scale.x)
	{
		return this->pos_count;
	}
	else if(dx < min_value)
	{
		return 0;
	}
	else
	{
		std::cout << std::round(dx / (double)pos_fraction) << std::endl;
		return std::round(dx / (double)pos_fraction);
	}
}

bool UI_Slider::in_bounds(Ivec point)
{
	const int bar_width  = 10 * scale.x;
	const int bar_height = 30 * scale.y;
	Ivec slider_pos			= Ivec(get_pos().x + (size.x - bar_width) * state / pos_count,
								   get_pos().y - (bar_height - size.y) / 2);
	Ivec slider_bottom_left = Ivec(slider_pos.x + bar_width,
								   slider_pos.y + bar_height);
	return UI_Base::in_bounds(point) ||
		(slider_pos.x <= point.x &&
		point.x <= slider_bottom_left.x &&
		slider_pos.y <= point.y &&
		point.y <= slider_bottom_left.y);
}

int UI_Slider::get_value()
{
	return this->state * (this->difference / (double)this->pos_count);
}

int UI_Slider::get_state()
{
	return this->state;
}

void UI_Slider::set_state(int state)
{
	this->state = state;
}

void UI_Slider::set_bind(int* value)
{
	this->binded_value = value;
	this->state = *value;
}
