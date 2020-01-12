#include "inventory.hpp"

Inventory::Inventory(Entity* parent, SDL_Renderer* renderer) :
Renderable(renderer)
{
	this->parent = parent;
	this->selection = 0;

	this->pos = Ivec(600, 524);
}

Inventory::~Inventory()
{
	for(Item* item : items)
	{
		delete item;
	}
};

void Inventory::update()
{
}

void Inventory::render()
{
	for(Item* item : items)
	{
		item->render();
	}
	for(int i = 0; i < 5; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			SDL_Rect rect = { pos.x + (i % 5) * 38, pos.y + j * 38, 36, 36 };
			if(i + j * 5 == selection)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			}
			SDL_RenderDrawRect(renderer, &rect);
		}
	}
}

Item* Inventory::get_current()
{
	return items[selection];
}

void Inventory::pick_item(Item* item)
{
	this->items.push_back(item);
	// TODO make dependent on slots available
	item->set_e_pos(Ivec(pos.x + 2, pos.y + 2));
}

Item* Inventory::drop_item(int pos)
{
	Item* item = items[pos];
	this->items.erase(this->items.begin() + pos);
	return item;
}

void Inventory::left()
{
	if(selection > 4)
	{
		// initially it was greater than 4
		selection--;
		if(selection < 5)
		{
			selection = 9;
		}
	}
	else
	{
		// initially it was less than 4
		this->selection--;
		if(selection < 0)
		{
			selection = 4;
		}
	}
}
void Inventory::down()
{
	this->selection += 5;
	if(this->selection > 9)
	{
		this->selection -= 10;
	}
}
void Inventory::up()
{
	this->selection -= 5;
	if(this->selection < 0)
	{
		this->selection += 10;
	}
}
void Inventory::right()
{
	if(selection > 4)
	{
		// initially it was greater than 4
		selection++;
		if(selection > 9)
		{
			selection = 5;
		}
	}
	else
	{
		// initially it was less than 4
		this->selection++;
		if(selection > 4)
		{
			selection = 0;
		}
	}
}
