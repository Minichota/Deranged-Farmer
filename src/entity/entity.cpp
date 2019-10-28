#include <cassert>

#include "entity.hpp"

Entity::Entity(SDL_Renderer* renderer, Ivec pos, Ivec size):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
}

Entity::Entity(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
}

Entity::Entity(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Ivec origin):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
	this->origin = origin;
}

Entity::~Entity()
{
	SDL_DestroyTexture(texture);
}

void Entity::set_texture(SDL_Texture* texture)
{
	assert(texture != nullptr);
	this->texture = texture;
}

SDL_Texture* Entity::get_texture()
{
	return this->texture;
}

void Entity::set_pos(Ivec pos)
{
	this->pos = pos;
}

Ivec& Entity::get_pos()
{
	return this->pos;
}

void Entity::set_size(Ivec size)
{
	this->size = size;
}

Ivec& Entity::get_size()
{
	return this->size;
}

void Entity::set_scale(Fvec scale)
{
	this->scale = scale;
}

Fvec& Entity::get_scale()
{
	return this->scale;
}

void Entity::set_origin(Ivec origin)
{
	this->origin = origin;
}

Ivec& Entity::get_origin()
{
	return this->origin;
}
