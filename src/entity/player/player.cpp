#include "player.hpp"
#include "vectors.hpp"

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size):
Entity(renderer, pos, size)
{
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
Entity(renderer, pos, size, scale)
{
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Ivec origin):
Entity(renderer, pos, size, scale, origin)
{
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render()
{
	SDL_Rect box =
	{
		pos.x,
		pos.y,
		size.x,
		size.y
	};
	SDL_RenderCopy(renderer, texture, NULL, &box);
}

void Player::handle_event(SDL_Event event)
{
}
