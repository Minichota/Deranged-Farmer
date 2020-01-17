#ifndef INVENTORY_CPP
#define INVENTORY_CPP

#include <vector>

#include "entity.hpp"
#include "item.hpp"
#include "renderable.hpp"

class Inventory : public Renderable
{
	public:
	Inventory(Entity* parent, SDL_Renderer* renderer);
	~Inventory();

	void update();
	void render();

	Item* get_current();

	bool pick_item(Item* item);
	Item* drop_item();

	void left();
	void down();
	void up();
	void right();

	private:
	Entity* parent;
	std::vector<Item*> items;
	int selection;

	Ivec pos;
};

#endif
