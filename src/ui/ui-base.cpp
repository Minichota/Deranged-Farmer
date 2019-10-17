#include "ui-base.hpp"

UI_Base::UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color color):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
	this->color = color;
}

UI_Base::UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
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
	this->color = {r,g,b,a};
}

void UI_Base::set_color(SDL_Color color)
{
	this->color = color;
}

SDL_Color& UI_Base::get_color()
{
	return this->color;
}

void UI_Base::set_pos(Ivec pos)
{
	this->pos = pos;
}

Ivec& UI_Base::get_pos()
{
	return this->pos;
}

void UI_Base::set_scale(Fvec scale)
{
	this->scale = scale;
}

Fvec& UI_Base::get_scale()
{
	return this->scale;

}

bool UI_Base::in_bounds(Ivec input_pos)
{
	Ivec actual_size = this->size * this->scale;
	Ivec bottom_left = Ivec(this->pos.x + actual_size.x,
							this->pos.y + actual_size.y);
	return this->pos.x <= input_pos.x &&
			input_pos.x <= bottom_left.x &&
			this->pos.y <= input_pos.y &&
			input_pos.y <= bottom_left.y;
}
