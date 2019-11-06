#include <iostream>
#include <cmath>
#include <math.h>

#include "player.hpp"
#include "vectors.hpp"
#include "util.hpp"
#include "game.hpp"

#define MAX_VEL 3.2f

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size):
Entity(renderer, pos, size)
{
	this->max_vel = Fvec(MAX_VEL,MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
Entity(renderer, pos, size, scale)
{
	this->max_vel = Fvec(MAX_VEL,MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Ivec origin):
Entity(renderer, pos, size, scale, origin)
{
	this->max_vel = Fvec(MAX_VEL,MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
}

Player::~Player()
{
}

void Player::update()
{
	handle_input();
	handle_physics();
}

void Player::render()
{
	SDL_Rect box =
	{
		(int)std::round(pos.x),
		(int)std::round(pos.y),
		(int)std::round(size.x),
		(int)std::round(size.y)
	};
	Ivec mouse_pos;
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	float mouse_angle = 180/M_PI * atan2(mouse_pos.y - this->pos.y, mouse_pos.x - this->pos.x) + 90;
	SDL_RenderCopyEx(renderer, texture, NULL, &box, mouse_angle, NULL, SDL_FLIP_NONE);
	if(Game::debug->active)
	{
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &box);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		Game::debug->push_render(this, "Player", {&this->pos, &this->size});
	}
}

void Player::handle_input()
{
	if(keys[SDL_SCANCODE_W])
	{
		accelerate(Fvec(0.0f, -1.0f));
	}
	if(keys[SDL_SCANCODE_A])
	{
		accelerate(Fvec(-1.0f, 0.0f));
	}
	if(keys[SDL_SCANCODE_S])
	{
		accelerate(Fvec(0.0f, 1.0f));
	}
	if(keys[SDL_SCANCODE_D])
	{
		accelerate(Fvec(1.0f, 0.0f));
	}
}
