#include <cassert>
#include <cmath>

#include "entity.hpp"

Entity::Entity(SDL_Renderer* renderer, Fvec pos, Fvec size):
Renderable(renderer),
Sized(pos, size)
{
	this->scale = Fvec(1.0f, 1.0f);
}

Entity::Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale):
Renderable(renderer),
Sized(pos, size)
{
	this->scale = scale;
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

void Entity::set_vel(Fvec vel)
{
	this->vel = vel;
}

Fvec& Entity::get_vel()
{
	return this->vel;
}

void Entity::set_scale(Fvec scale)
{
	this->scale = scale;
}

Fvec& Entity::get_scale()
{
	return this->scale;
}
