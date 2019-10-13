#include "ui-base.hpp"

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
