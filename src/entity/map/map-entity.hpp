#ifndef MAP_ENTITY_HPP
#define MAP_ENTITY_HPP

#include "entity.hpp"

class Map_Entity : public Entity
{
	public:
	Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int rotation);
	~Map_Entity();

	void update();
	void render();

	void handle_event(SDL_Event event);

	private:
	int rotation;
};
#endif
