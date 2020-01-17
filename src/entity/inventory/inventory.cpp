#include "inventory.hpp"

Inventory::Inventory(Entity* parent, SDL_Renderer* renderer) :
Renderable(renderer)
{
	this->parent = parent;
	this->selection = 0;

	this->pos = Ivec(600, 524);
	items.reserve(10);
	for(size_t i = 0; i < 10; i++)
	{
		items.push_back(nullptr);
	}
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
		if(item != nullptr)
		{
			item->render();
		}
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
	if(selection >= (int)items.size())
	{
		return nullptr;
	}
	return items[selection];
}

bool Inventory::pick_item(Item* item)
{
	size_t slot = 0;
	if(items[selection] != nullptr)
	{
		for(;; slot++)
		{
			if(slot >= items.size())
			{
				return false;
			}
			if(items[slot] == nullptr)
			{
				this->items[slot] = item;
				break;
			}
		}
	}
	else
	{
		slot = selection;
		this->items[selection] = item;
	}
	item->set_e_pos(
		Ivec(pos.x + 2 + (slot % 5) * 38, pos.y + 2 + (int)(slot / 5) * 38));
	return true;
}

Item* Inventory::drop_item()
{
	if(items[selection] != nullptr)
	{
		Item* item = items[selection];
		this->items[selection] = nullptr;
		item->set_e_pos(parent->get_pos());
		item->set_pos(parent->get_pos());
		return item;
	}
	return nullptr;
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
