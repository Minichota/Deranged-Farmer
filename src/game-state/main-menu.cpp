#include <iostream>

#include "main-menu.hpp"
#include "ui-base.hpp"
#include "ui-text.hpp"

MainMenu::MainMenu(SDL_Renderer* renderer):
GameState(renderer)
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
	UI_Text* text_element = new UI_Text(renderer, Ivec(0,0), Ivec(500, 50), Fvec(1.0f,1.0f),
			"Deranged farmer", "res/graphics/font.ttf", SDL_Color{255,255,255});
	elements.push_back(text_element);
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
