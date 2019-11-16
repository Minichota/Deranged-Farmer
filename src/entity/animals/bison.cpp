#include <cassert>

#include "bison.hpp"
#include "game.hpp"

Bison::Bison(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale):
Entity(renderer, pos, size, scale)
{
	this->rotation = 0;
	this->max_vel = Fvec(2.2f, 2.2f);
}

Bison::Bison(SDL_Renderer* renderer, Fvec pos, Fvec size):
Entity(renderer, pos, size, Fvec(1.0f,1.0f))
{
	this->rotation = 0;
	this->max_vel = Fvec(2.2f, 2.2f);
}

Bison::~Bison()
{
}

void Bison::update()
{
	handle_physics();
}

void Bison::render()
{
	SDL_Rect dest_rect = get_simple_rect();
	SDL_RenderCopyEx(renderer, texture, NULL, &dest_rect, rotation, NULL, SDL_FLIP_NONE);
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Bison", {&this->pos.x, &this->pos.y,
												 &this->vel.x, &this->vel.y,
												 &this->size.x, &this->size.y,
												 &this->rotation});
	}
}

void Bison::handle_event(SDL_Event event)
{
}
