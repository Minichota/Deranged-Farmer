#include <iostream>

#include "player.hpp"
#include "vectors.hpp"

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size):
Entity(renderer, pos, size)
{
	this->max_vel = Fvec(5.5f,5.5f);
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
Entity(renderer, pos, size, scale)
{
	this->max_vel = Fvec(5.5f,5.5f);
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Ivec origin):
Entity(renderer, pos, size, scale, origin)
{
	this->max_vel = Fvec(5.5f,5.5f);
}

Player::~Player()
{
}

void Player::update()
{
	move();
	handle_physics();
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
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_w:
				{
					accelerate(Fvec(0.0f, -5.0f));
				} break;
				case SDLK_a:
				{
					accelerate(Fvec(-1.0f, 0.0f));
				} break;
				case SDLK_s:
				{
				} break;
				case SDLK_d:
				{
					accelerate(Fvec(1.0f, 0.0f));
				} break;
			}
		} break;
	}
}
