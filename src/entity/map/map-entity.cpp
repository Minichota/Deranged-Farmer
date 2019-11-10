#include <cassert>

#include "map-entity.hpp"
#include "game.hpp"

Map_Entity::Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int rotation):
Entity(renderer, pos, size)
{
	this->rotation = rotation % 180;
}

Map_Entity::~Map_Entity()
{
}

void Map_Entity::update()
{
}

void Map_Entity::render()
{
	SDL_Rect output_rect =
	{
		(int)std::round(pos.x),
		(int)std::round(pos.y),
		(int)std::round(size.x),
		(int)std::round(size.y)
	};
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Entity", {&pos.x, &pos.y,
												  &size.x, &size.y});
	}
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	SDL_RenderCopyEx(renderer, texture, NULL, &output_rect, this->rotation, NULL, SDL_FLIP_NONE);
}

void Map_Entity::handle_event(SDL_Event event)
{
}

Fvec Map_Entity::get_pos_copy()
{
	float rad_rotation = -rotation * 3.1415926535f / 180;
	assert(rotation >= 0);
	float p = pos.x + size.x/2;
	float q = pos.y + size.y/2;
	Fvec pos_prime = Fvec((-size.x/2) * cosf(rad_rotation) - (-size.y/2) * sinf(rad_rotation) + p,
						  (size.x/2) * sinf(rad_rotation) + (-size.y/2) * cosf(rad_rotation) + q);
	return pos_prime;
}

Fvec Map_Entity::get_size_copy()
{
	switch(rotation)
	{
		case 90:
		case 270:
		{
			return Fvec(size.y, size.x);
		} break;
		default:
		{
			return this->size;
		} break;
	}
}
