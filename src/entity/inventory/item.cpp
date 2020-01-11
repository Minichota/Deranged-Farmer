#include "item.hpp"
#include "level.hpp"

Item::Item(SDL_Renderer* renderer, Level* level, Ivec pos, std::string file_path):
Renderable(renderer)
{
	this->level = level;
	this->texture = nullptr;
	this->pos = pos;

	{
		this->texture = IMG_LoadTexture(renderer, file_path.c_str());
		Error(this->texture == nullptr, {"Failed to load item texture: ", file_path.c_str()});
	}
}

Item::~Item()
{
	SDL_DestroyTexture(this->texture);
}

void Item::update()
{
}

void Item::render()
{
	SDL_Rect source { 0, 0, 32, 32 };
	SDL_Rect dest { pos.x, pos.y, 32, 32 };
	SDL_RenderCopy(renderer, this->texture, &source, &dest);
}

void Item::use()
{
}

void Item::pick()
{
	dropped = false;
}

Ivec Item::get_pos()
{
	return this->pos;
}

void Item::set_pos(Ivec pos)
{
	this->pos = pos;
}

Ivec Item::get_size()
{
	return Ivec(32, 32);
}
