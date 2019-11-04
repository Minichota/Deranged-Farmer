#include <cassert>
#include <cmath>

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

void Entity::handle_event(SDL_Event e)
{
}

void Entity::set_texture(SDL_Texture* texture)
{
	assert(texture != nullptr);
	this->texture = texture;
}

void Entity::accelerate(Fvec vel)
{
	this->vel += vel;
	if(this->vel.x > max_vel.x)
	{
		this->vel.x = max_vel.x;
	}
	else if(this->vel.x < -max_vel.x)
	{
		this->vel.x = -max_vel.x;
	}
   	if(this->vel.y > max_vel.y)
	{
		this->vel.y = max_vel.y;
	}
   	else if(this->vel.y < -max_vel.y)
	{
		this->vel.y = -max_vel.y;
	}
}

void Entity::handle_physics()
{
	Fvec final_application;
	if(this->vel.x > 0)
	{
		final_application.x = -0.2f;
		if(vel.x + final_application.x < 0)
		{
			final_application.x = -vel.x;
		}
	}
	else if(this->vel.x < 0)
	{
		final_application.x = 0.2f;
		if(vel.x + final_application.x > 0)
		{
			final_application.x = -vel.x;
		}
	}
	if(this->vel.y > 0)
	{
		final_application.y = -0.2f;
		if(vel.y + final_application.y < 0)
		{
			final_application.x = -vel.x;
		}
	}
	else if(this->vel.y < 0)
	{
		final_application.y = 0.2f;
		if(vel.y + final_application.y > 0)
		{
			final_application.y = -vel.y;
		}
	}
	accelerate(final_application);
}

void Entity::move()
{
	this->pos.x = std::round(this->pos.x + this->vel.x);
	this->pos.y = std::round(this->pos.y + this->vel.y);
}

void Entity::set_health(int health)
{
	this->health = health;
	if(this->health < 0)
	{
		this->health = 0;
	}
}

void Entity::heal(int health)
{
	this->health += health;
	if(this->health > max_health)
	{
		this->health = max_health;
	}
}

void Entity::damage(int health)
{
	this->health -= health;
	if(this->health < 0)
	{
		this->health = 0;
	}
}

int& Entity::get_health()
{
	return this->health;
}

int& Entity::get_max_health()
{
	return this->max_health;
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

void Entity::set_vel(Fvec vel)
{
	this->vel = vel;
}

Fvec& Entity::get_vel()
{
	return this->vel;
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
	// TODO make more comparisons in vector class
	assert(this->origin.x <= this->size.x &&
		   this->origin.y <= this->size.y);
}

Ivec& Entity::get_origin()
{
	return this->origin;
}
