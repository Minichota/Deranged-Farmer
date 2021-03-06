#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "event-handler.hpp"
#include "renderable.hpp"
#include "sized.hpp"
#include "vectors.hpp"

class Entity : public Renderable, public Event_Handler, public Sized<float>
{
	public:
	Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, int type,
		   int rotation = 0);
	Entity(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale, int type,
		   int rotation = 0);
	virtual ~Entity();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void handle_event(const SDL_Event& event);

	// physics
	void accelerate(Fvec vel);
	void handle_physics();
	void move();

	// attributed
	void set_health(int health);
	void heal(int health);
	void damage(int health);
	int& get_health();
	int& get_max_health();

	void set_texture(SDL_Texture* texture);
	void load_texture(std::string texture_path);
	SDL_Texture* get_texture();

	void set_vel(Fvec vel);
	Fvec& get_vel();

	int get_type();

	protected:
	Fvec vel;
	Fvec max_vel;

	int health;
	int max_health;

	int type;

	SDL_Texture* texture = nullptr;
};
#endif
