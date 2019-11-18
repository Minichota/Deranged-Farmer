#include <cassert>

#include "map-entity.hpp"
#include "game.hpp"

Map_Entity::Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int rotation):
Entity(renderer, pos, size, rotation)
{
}

Map_Entity::~Map_Entity()
{
}

void Map_Entity::update()
{
}

void Map_Entity::render()
{
	SDL_Rect output_rect = get_render_rect();
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Entity", {&pos.x, &pos.y,
												  &size.x, &size.y});
	}
	SDL_SetRenderDrawColor(renderer, 255,255,255,255);
	SDL_RenderCopyEx(renderer, texture, NULL, &output_rect, this->rotation, NULL, SDL_FLIP_NONE);
}
