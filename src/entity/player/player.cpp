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
	SDL_Rect box = get_simple_rect();
	Ivec mouse_pos;
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	float mouse_angle = 180/M_PI * atan2(mouse_pos.y - (this->pos.y + this->size.y * scale.y / 2), mouse_pos.x - (this->pos.x + this->size.x * scale.x / 2)) + 90;
	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_RenderCopyEx(renderer, texture, NULL, &box, mouse_angle, NULL, SDL_FLIP_NONE);
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Player", {&this->pos.x, &this->pos.y,
												  &this->size.x, &this->size.y,
												  &this->scale.x, &this->scale.y,
												  &this->max_vel.x, &this->max_vel.y});
	}
	clear_render_settings(renderer);
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
