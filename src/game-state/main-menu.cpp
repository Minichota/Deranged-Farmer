#include <iostream>

#include "main-menu.hpp"
#include "ui-base.hpp"
#include "ui-text.hpp"
#include "ui-button.hpp"
#include "ui-slider.hpp"
#include "ui-switch.hpp"
#include "ui-text-input.hpp"
#include "ui-rect.hpp"
#include "interpolators.hpp"
#include "game.hpp"

MainMenu::MainMenu(SDL_Renderer* renderer):
Game_State(renderer)
{
}

MainMenu::~MainMenu()
{
	clear();
}

void MainMenu::update()
{
	update_interpolators();
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
void test()
{
	Game::increment_state();
}

void MainMenu::init()
{
	elements = {
		new UI_Rect(renderer, Ivec(400,100), Ivec(100, 100), Fvec(2.0f,1.5f), SDL_Color{255,0,255,255}, NORMAL),
		new UI_Text(renderer, Ivec(400,100), Ivec(0, 0), Fvec(2.0f,1.5f), "Deranged farmer", "res/graphics/font.ttf", SDL_Color{0,255,255}, NORMAL),
		new UI_Button(renderer, Ivec(400,300), Ivec(40,20), Fvec(5.0f,5.0f), &test, SDL_Color{255,0,0,255}),
		new UI_Text(renderer, Ivec(400,300), Ivec(192, 100), Fvec(1.0f,1.0f), "Start", "res/graphics/font.ttf", SDL_Color{255,255,255}, FILL)
	};

	dynamic_cast<UI_Text*>(elements[1])->set_font_size(30);

	elements[0]->set_size(elements[1]->get_size());

	elements[0]->set_origin(elements[0]->get_size()/2.0f);
	elements[1]->set_origin(elements[1]->get_size()/2.0f);
	elements[2]->set_origin(elements[2]->get_size()/2.0f);
	elements[3]->set_origin(elements[3]->get_size()/2.0f);

	float_interpolaters.push_back(Interpolator<float>{&elements[1]->get_scale().x, 1.0f, 2.0f, 1000, 1000, false, OSCILLATOR});
	float_interpolaters.push_back(Interpolator<float>{&elements[1]->get_scale().y, 0.75f, 1.5f, 2000, 2000, false, OSCILLATOR});

	float_interpolaters.push_back(Interpolator<float>{&elements[0]->get_scale().x, 1.02f, 2.04f, 1000, 1000, false, OSCILLATOR});
	float_interpolaters.push_back(Interpolator<float>{&elements[0]->get_scale().y, 0.765f, 1.53f, 2000, 2000, false, OSCILLATOR});
}

void MainMenu::clear()
{
	for(UI_Base* element : elements)
	{
		delete element;
	}
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
