#include <iostream>

#include "main-menu.hpp"
#include "ui-base.hpp"
#include "ui-text.hpp"
#include "ui-button.hpp"
#include "ui-slider.hpp"
#include "ui-switch.hpp"
#include "ui-text-input.hpp"
#include "interpolators.hpp"
#include "game.hpp"

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

	update_interpolators();
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
		new UI_Text(renderer, Ivec(500,50), Ivec(500, 50), Fvec(2.0f,1.5f), "Deranged farmer", "res/graphics/font.ttf", SDL_Color{255,255,255}),
		new UI_Button(renderer, Ivec(500,200), Ivec(20,20), Fvec(1.0f,1.0f), &test, SDL_Color{255,0,0,255}),
		new UI_Slider(renderer, Ivec(500,500), Ivec(100,10), Fvec(1.0f,1.0f), 0, 100, 100, SDL_Color{0,255,0,255}),
		new UI_Switch(renderer, Ivec(500,700), Ivec(100,100), Fvec(1.0f,1.0f), SDL_Color{0,0,255,255}),
		new UI_Text_Input(renderer, Ivec(0,500), Ivec(1000,200), Fvec(2.0f,2.0f), "res/graphics/font.ttf", SDL_Color{255,255,0,255})
	};

	elements[0]->set_origin(elements[0]->get_size()/2);
	elements[1]->set_origin(elements[1]->get_size()/2);
	elements[2]->set_origin(elements[2]->get_size()/2);
	elements[3]->set_origin(elements[3]->get_size()/2);
	elements[4]->set_origin(elements[4]->get_size()/2);

	ivec_interpolaters.push_back(Interpolator<Ivec>{&elements[3]->get_abs_pos(), Ivec(400,700), Ivec(600,700), 1000, 1000, false, OSCILLATOR});
	//float_interpolaters.push_back(Interpolator<float>{&elements[3]->get_scale().x, 1.0f, 2.0f, 1000, 1000, false, OSCILLATOR});
	//float_interpolaters.push_back(Interpolator<float>{&elements[3]->get_scale().y, 1.0f, 2.0f, 1000, 1000, false, OSCILLATOR});

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
