#include "map-entity.hpp"
#include "game.hpp"

Map_Entity::Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size):
Entity(renderer, pos, size)
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
	SDL_Rect output_rect =
	{
		(int)std::round(pos.x),
		(int)std::round(pos.y),
		(int)std::round(size.x),
		(int)std::round(size.y)
	};
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Entity", {&pos.x, &pos.x,
												  &size.x, &size.y});
	}
	SDL_RenderCopy(renderer, texture, NULL, &output_rect);
}

void Map_Entity::handle_event(SDL_Event event)
{
}
