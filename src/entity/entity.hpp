#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "renderable.hpp"
#include "vectors.hpp"
#include "event-handler.hpp"

class Entity : public Renderable, public Event_Handler
{
	public:
	Entity(SDL_Renderer* renderer, Ivec pos, Ivec size);
	Entity(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale);
	Entity(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Ivec origin);
	virtual ~Entity();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void handle_event(SDL_Event event);

	void accelerate(Fvec vel);
	void handle_physics();
	void move();

	void set_health(int health);
	void heal(int health);
	void damage(int health);
	int& get_health();
	int& get_max_health();

	void set_texture(SDL_Texture* texture);
	SDL_Texture* get_texture();

	void set_pos(Ivec pos);
	Ivec& get_pos();

	void set_vel(Fvec vel);
	Fvec& get_vel();

	void set_size(Ivec size);
	Ivec& get_size();

	void set_scale(Fvec size);
	Fvec& get_scale();

	void set_origin(Ivec origin);
	Ivec& get_origin();

	protected:
	Ivec pos;
	Fvec vel;
	Ivec size;
	Fvec scale;
	Ivec origin;

	Fvec max_vel;

	int health;
	int max_health;

	SDL_Texture* texture;
};
#endif
