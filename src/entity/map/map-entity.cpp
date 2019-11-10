#include "map-entity.hpp"
#include "game.hpp"

Map_Entity::Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int rotation):
Entity(renderer, pos, size)
{
	this->rotation = rotation;
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
	SDL_RenderCopyEx(renderer, texture, NULL, &output_rect, this->rotation, NULL, SDL_FLIP_NONE);
}

void Map_Entity::handle_event(SDL_Event event)
{
}
