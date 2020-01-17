#include <cassert>

#include "game.hpp"
#include "map-entity.hpp"

Map_Entity::Map_Entity(SDL_Renderer* renderer, int type, Fvec pos, Fvec size,
					   int rotation) :
Entity(renderer, pos, size, rotation)
{
	this->type = type;
}

void Map_Entity::update()
{
}

void Map_Entity::render()
{
	SDL_Rect output_rect = get_render_rect();
	if(Game::debug->active)
	{
		Game::debug->push_render(
			this, "Entity", { &pos.x, &pos.y, &size.x, &size.y, &rotation });
	}
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderCopyEx(renderer, texture, NULL, &output_rect, this->rotation,
					 NULL, SDL_FLIP_NONE);
}

int Map_Entity::get_type()
{
	return this->type;
}
