#include <iostream>

#include "main-menu.hpp"
#include "ui-base.hpp"
#include "ui-text.hpp"
#include "ui-button.hpp"
#include "ui-slider.hpp"

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
	std::cout << (dynamic_cast<UI_Slider*>(elements[2]))->get_value() << std::endl;
}

void MainMenu::render()
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->render();
	}
}

void test()
{
	std::cout << "button pressed, \n all is well" << std::endl;
}

void MainMenu::init()
{
	UI_Text* text_element = new UI_Text(renderer, Ivec(0,0), Ivec(500, 50), Fvec(2.0f,0.5f),
			"Deranged farmer", "res/graphics/font.ttf", SDL_Color{255,255,255});
	UI_Button* button = new UI_Button(renderer, Ivec(0,200), Ivec(20,20), Fvec(10.0f,10.0f), &test);
	UI_Slider* slider = new UI_Slider(renderer, Ivec(0,500), Ivec(100,10), Fvec(1.0f,1.0f), 0, 100, 2);
	elements.push_back(text_element);
	elements.push_back(button);
	elements.push_back(slider);
}

void MainMenu::clear()
{
	elements.clear();
}

void MainMenu::handle_event(SDL_Event event)
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		Event_Handler* element = dynamic_cast<Event_Handler*>(elements[i]);
		if(element != nullptr)
		{
			element->handle_event(event);
		}
	}
}

void MainMenu::push_element(UI_Base* element)
{
	elements.push_back(element);
}

UI_Base* MainMenu::get_element(size_t index)
{
	return elements[index];
}
