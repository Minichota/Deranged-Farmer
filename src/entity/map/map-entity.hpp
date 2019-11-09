#include "entity.hpp"

class Map_Entity : public Entity
{
	public:
	Map_Entity(SDL_Renderer* renderer, Fvec pos, Fvec size);
	~Map_Entity();

	void update();
	void render();

	void handle_event(SDL_Event event);
};
