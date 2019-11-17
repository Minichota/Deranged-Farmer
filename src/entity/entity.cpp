#include <cassert>
#include <cmath>

#include "entity.hpp"
#include "error.hpp"

Entity::Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int rotation):
Renderable(renderer),
Sized(pos, size, Fvec(1.0f, 1.0f), rotation)
{
}

Entity::Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale, int rotation):
Renderable(renderer),
Sized(pos, size, scale, rotation)
{
}

Entity::~Entity()
{
	SDL_DestroyTexture(texture);
}

void Entity::handle_event(SDL_Event e)
{
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
			final_application.y = -vel.y;
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
	// handing rotation
	if(vel.x > 0.0f)
	{
		this->rotation = 180;
	}
	else if(vel.x < 0.0f)
	{
		this->rotation = 0;
	}
	if(vel.y > 0.0f)
	{
		this->rotation = 270;
	}
	else if(vel.y < 0.0f)
	{
		this->rotation = 90;
	}
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

void Entity::load_texture(std::string texture_path)
{
	this->texture = IMG_LoadTexture(renderer, texture_path.c_str());
	Error(!texture, {"failed to load texture from: ", texture_path.c_str()});
}

void Entity::set_texture(SDL_Texture* texture)
{
	Error(!texture, {"failed to copy texture, it is null: "});
	this->texture = texture;
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
