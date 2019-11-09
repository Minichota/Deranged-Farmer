#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "renderable.hpp"
#include "vectors.hpp"
#include "event-handler.hpp"
#include "sized.hpp"

class Entity : public Renderable, public Event_Handler, public Sized<float>
{
	public:
	Entity(SDL_Renderer* renderer, Fvec pos, Fvec size);
	Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale);
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

	void set_vel(Fvec vel);
	Fvec& get_vel();

	protected:
	Fvec vel;

	Fvec max_vel;

	int health;
	int max_health;

	SDL_Texture* texture;
};
#endif
