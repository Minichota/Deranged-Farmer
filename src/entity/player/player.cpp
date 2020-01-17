#include <cmath>
#include <iostream>
#include <math.h>

#include "game.hpp"
#include "player.hpp"
#include "util.hpp"
#include "vectors.hpp"

#define MAX_VEL 3.2f

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size) :
Entity(renderer, pos, size),
idle_animation(renderer, this, "res/graphics/player.png", size, 1500),
moving_animation(renderer, this, "res/graphics/player_moving.png", size, 1500),
inventory(this, renderer)
{
	this->max_vel = Fvec(MAX_VEL, MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
	idle_animation.init();
	moving_animation.init();
}

Player::Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale) :
Entity(renderer, pos, size, scale),
idle_animation(renderer, this, "res/graphics/player.png", size, 1500),
moving_animation(renderer, this, "res/graphics/player_moving.png", size, 1500),
inventory(this, renderer)
{
	this->max_vel = Fvec(MAX_VEL, MAX_VEL);
	this->max_health = 100;
	set_health(max_health);
	idle_animation.init();
	moving_animation.init();
}

Player::~Player()
{
	idle_animation.clear();
	moving_animation.clear();
}

void Player::update()
{
	handle_input();
	handle_physics();
}

void Player::render()
{
	inventory.render();
	// fix rendering
	this->rotation -= 90;
	if(abs(this->vel.x) > 0.5f || abs(this->vel.y) > 0.5f)
	{
		moving_animation.render();
	}
	else
	{
		idle_animation.render();
	}
	if(Game::debug->active)
	{
		Game::debug->push_render(
			this, "Player",
			{ &this->pos.x, &this->pos.y, &this->size.x, &this->size.y,
			  &this->scale.x, &this->scale.y, &this->max_vel.x,
			  &this->max_vel.y, &this->vel.x, &this->vel.y });
	}
	this->rotation += 90;
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
	Item* item = inventory.get_current();
	if(item != nullptr && !keys[SDL_SCANCODE_LCTRL])
	{
		if(keys[SDL_SCANCODE_H])
		{
			item->use(H);
		}
		else if(keys[SDL_SCANCODE_J])
		{
			item->use(J);
		}
		else if(keys[SDL_SCANCODE_K])
		{
			item->use(K);
		}
		else if(keys[SDL_SCANCODE_L])
		{
			item->use(L);
		}
	}
}

void Player::handle_event(const SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_h:
				{
					if(keys[SDL_SCANCODE_LCTRL])
					{
						inventory.left();
					}
				}
				break;
				case SDLK_j:
				{
					if(keys[SDL_SCANCODE_LCTRL])
					{
						inventory.down();
					}
				}
				break;
				case SDLK_k:
				{
					if(keys[SDL_SCANCODE_LCTRL])
					{
						inventory.up();
					}
				}
				break;
				case SDLK_l:
				{
					if(keys[SDL_SCANCODE_LCTRL])
					{
						inventory.right();
					}
				}
				break;
			}
		}
		break;
	}
}

Inventory& Player::get_inventory()
{
	return this->inventory;
}
