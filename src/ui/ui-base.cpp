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
