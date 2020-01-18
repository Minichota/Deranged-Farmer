#include "bison.hpp"
#include "game.hpp"

Bison::Bison(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale) :
Entity(renderer, pos, size, scale, 0),
animation(renderer, this, "res/graphics/bison.png", size, 1500)
{
	animation.init();
	this->rotation = 0;
	this->max_vel = Fvec(1.2f, 1.2f);
}

Bison::Bison(SDL_Renderer* renderer, Fvec pos, Fvec size) :
Entity(renderer, pos, size, Fvec(1.0f, 1.0f), 0),
animation(renderer, this, "res/graphics/bison.png", size, 1500)
{
	animation.init();
	this->rotation = 0;
	this->max_vel = Fvec(1.2f, 1.2f);
}

Bison::~Bison()
{
	animation.clear();
}

void Bison::update()
{
	handle_physics();
}

void Bison::render()
{
	animation.render();
}
