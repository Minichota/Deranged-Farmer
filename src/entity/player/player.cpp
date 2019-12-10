#include <iostream>
#include <cmath>
#include <math.h>

#include "player.hpp"
#include "vectors.hpp"
#include "util.hpp"
#include "game.hpp"

#define MAX_VEL 3.2f

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size):
Entity(renderer, pos, size),
animation(renderer, this, "res/graphics/player.png", size, 500)
{
	this->max_vel = Fvec(MAX_VEL,MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
	animation.init();
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
Entity(renderer, pos, size, scale),
animation(renderer, this, "res/graphics/player.png", size, 500)
{
	this->max_vel = Fvec(MAX_VEL,MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
	animation.init();
}

Player::~Player()
{
	animation.clear();
}

void Player::update()
{
	handle_input();
	handle_physics();
}

void Player::render()
{
	Ivec mouse_pos;
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	this->rotation  = 180/M_PI * atan2(mouse_pos.y - (this->pos.y + this->size.y * scale.y / 2), mouse_pos.x - (this->pos.x + this->size.x * scale.x / 2)) + 90;
	animation.render();
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Player", {&this->pos.x, &this->pos.y,
												  &this->size.x, &this->size.y,
												  &this->scale.x, &this->scale.y,
												  &this->max_vel.x, &this->max_vel.y,
												  &this->vel.x, &this->vel.y});
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
