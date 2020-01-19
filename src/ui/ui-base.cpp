#include <iostream>

#include "ui-base.hpp"
#include "util.hpp"

UI_Base::UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale,
				 SDL_Color color) :
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
	this->color = color;
}

UI_Base::UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale) :
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
}

UI_Base::~UI_Base()
{
}

void UI_Base::set_color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->color = { r, g, b, a };
}

void UI_Base::set_color(SDL_Color color)
{
	this->color = color;
}

SDL_Color& UI_Base::get_color()
{
	return this->color;
}

void UI_Base::set_abs_pos(Ivec pos)
{
	this->pos = pos;
}

Ivec& UI_Base::get_abs_pos()
{
	return this->pos;
}

Ivec UI_Base::get_pos()
{
	return pos / scale - origin;
}

void UI_Base::set_size(Ivec size)
{
	this->size = size;
}

Ivec& UI_Base::get_size()
{
	return this->size;
}

void UI_Base::set_scale(Fvec scale)
{
	this->scale = scale;
}

Fvec& UI_Base::get_scale()
{
	return this->scale;
}

void UI_Base::set_origin(Ivec origin)
{
	this->origin = origin;
}

Ivec& UI_Base::get_origin()
{
	return this->origin;
}

bool UI_Base::in_bounds(Ivec input_pos)
{
	Ivec actual_size = this->size * this->scale;
	Ivec top_left = get_pos() * scale;
	Ivec bottom_left =
		Ivec(top_left.x + actual_size.x, top_left.y + actual_size.y);
	return top_left.x <= input_pos.x && input_pos.x <= bottom_left.x &&
		   top_left.y <= input_pos.y && input_pos.y <= bottom_left.y;
}

void UI_Base::handle_event(const SDL_Event& event)
{
}
