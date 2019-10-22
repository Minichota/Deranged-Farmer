#include "level.hpp"
#include "game.hpp"

Level::Level(SDL_Renderer* renderer, const char* entity_file_path, const char* map_file_path):
Game_State(renderer),
entity_file_path(entity_file_path),
map_file_path(map_file_path)
{
}

Level::~Level()
{
	clear();
}

void Level::update()
{
	//for(Entity* entity : entities)
	//{
	//	entity->update();
	//}

	for(UI_Base* ui_elem : elements)
	{
		ui_elem->update();
	}
}

void Level::render()
{
	//for(Entity* entity : entities)
	//{
	//	entity->render();
	//}

	for(UI_Base* ui_elem : elements)
	{
		ui_elem->render();
	}
}

void Level::init()
{
}

void Level::clear()
{
	//for(Entity* entity : entities)
	//{
	//	delete entity;
	//}
	//entities.clear()

	for(UI_Base* ui_elem : elements)
	{
		delete ui_elem;
	}
	elements.clear();
}

void Level::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					Game::toggle_pause();
				}
			}
		}
	}
}

void Level::push_element(UI_Base* element)
{
	elements.push_back(element);
}

UI_Base* Level::get_element(size_t index)
{
	return elements[index];
}
