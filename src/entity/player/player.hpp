#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"

class Player : public Entity
{
	public:
	Player(SDL_Renderer* renderer, Ivec pos, Ivec size);
	Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale);
	~Player();

	void update();
	void render();

	void handle_input();
};
#endif
