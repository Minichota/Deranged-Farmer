#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "entity.hpp"
#include "animation.hpp"
#include "inventory.hpp"
#include "event-handler.hpp"

class Player : public Entity, public Event_Handler
{
	public:
	Player(SDL_Renderer* renderer, Ivec pos, Ivec size);
	Player(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale);
	~Player();

	void update();
	void render();

	void handle_input();

	void handle_event(const SDL_Event& event);

	Inventory& get_inventory();

	private:
	Animation idle_animation;
	Animation moving_animation;

	Inventory inventory;
};
#endif
