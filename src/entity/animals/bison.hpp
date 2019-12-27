#ifndef BISON_HPP
#define BISON_HPP

#include "entity.hpp"
#include "animation.hpp"

class Bison : public Entity
{
	public:
	Bison(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale);
	Bison(SDL_Renderer* renderer, Fvec pos, Fvec size);
	~Bison();

	void update();
	void render();

	private:
	Animation animation;
};
#endif
