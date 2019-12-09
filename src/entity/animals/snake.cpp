#include "snake.hpp"
#include "game.hpp"

Snake::Snake(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale):
Entity(renderer, pos, size, scale)
{
	this->rotation = 0;
	this->max_vel = Fvec(1.2f, 1.2f);
}

Snake::Snake(SDL_Renderer* renderer, Fvec pos, Fvec size):
Entity(renderer, pos, size, Fvec(1.0f,1.0f))
{
	this->rotation = 0;
	this->max_vel = Fvec(1.2f, 1.2f);
}

Snake::~Snake()
{
}

void Snake::update()
{
	handle_physics();
}

void Snake::render()
{
	SDL_Rect dest_rect = get_render_rect();
	SDL_RenderCopyEx(renderer, texture, NULL, &dest_rect, rotation, NULL, SDL_FLIP_NONE);
	if(Game::debug->active)
	{
		Game::debug->push_render(this, "Snake", {&this->pos.x, &this->pos.y,
												 &this->vel.x, &this->vel.y,
												 &this->size.x, &this->size.y,
												 &this->rotation});
	}
}
