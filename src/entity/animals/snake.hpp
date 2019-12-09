#include "entity.hpp"

class Snake : public Entity
{
	public:
	Snake(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale);
	Snake(SDL_Renderer* renderer, Fvec pos, Fvec size);
	~Snake();

	void update();
	void render();
};
