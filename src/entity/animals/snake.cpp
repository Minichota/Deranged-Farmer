#include "snake.hpp"
#include "game.hpp"

Snake::Snake(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale) :
Entity(renderer, pos, size, scale),
animation(renderer, this, "res/graphics/snake.png", size, 2000)
{
	animation.init();
	this->rotation = 0;
	this->max_vel = Fvec(1.2f, 1.2f);
}

Snake::Snake(SDL_Renderer* renderer, Fvec pos, Fvec size) :
Entity(renderer, pos, size, Fvec(1.0f, 1.0f)),
animation(renderer, this, "res/graphics/snake.png", size, 2000)
{
	animation.init();
	this->rotation = 0;
	this->max_vel = Fvec(1.2f, 1.2f);
}

Snake::~Snake()
{
	animation.clear();
}

void Snake::update()
{
	handle_physics();
}

void Snake::render()
{
	animation.render();
}
