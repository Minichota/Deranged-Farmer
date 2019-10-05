#include "main-menu.hpp"
#include "ui-base.hpp"

MainMenu::MainMenu(SDL_Texture* world_texture):
GameState(world_texture)
{
}

MainMenu::~MainMenu()
{
	clear();
}

void MainMenu::update()
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->update();
	}
}

void MainMenu::render()
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->render();
	}
}

void MainMenu::init()
{
}

void MainMenu::clear()
{
	elements.clear();
}

void MainMenu::handle_event(SDL_Event event)
{
}

void MainMenu::push_element(UI_Base* element)
{
	elements.push_back(element);
}

UI_Base* MainMenu::get_element(size_t index)
{
	return elements[index];
}
