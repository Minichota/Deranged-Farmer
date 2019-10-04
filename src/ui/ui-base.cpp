#include "ui-base.hpp"

UI_Base::UI_Base(SDL_Texture* world_texture, Ivec pos, Ivec size, Fvec scale):
Renderable(world_texture)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
}

UI_Base::~UI_Base()
{
}
