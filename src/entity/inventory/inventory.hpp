#ifndef INVENTORY_CPP
#define INVENTORY_CPP

#include <vector>

#include "entity.hpp"
#include "renderable.hpp"
#include "item.hpp"

class Inventory : public Renderable
{
	public:
	Inventory(Entity* parent, SDL_Renderer* renderer);
	~Inventory();

	void update();
	void render();

	void pick_item(Item* item);
	Item* drop_item(int pos);

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
