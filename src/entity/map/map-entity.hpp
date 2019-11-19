#ifndef MAP_ENTITY_HPP
#define MAP_ENTITY_HPP

#include "entity.hpp"

class Map_Entity : public Entity
{
	public:
	Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int rotation = 0);

	void update();
	void render();
};
#endif
