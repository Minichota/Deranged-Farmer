#include "game.hpp"
#include "pause-menu.hpp"
#include "ui-text.hpp"

Pause_Menu::Pause_Menu(SDL_Renderer* renderer):
Game_State(renderer)
{
}

Pause_Menu::~Pause_Menu()
{
	clear();
}

void Pause_Menu::update()
{
	for(UI_Base* element : elements)
	{
		element->update();
	}
}

void Pause_Menu::render()
{
	for(UI_Base* element : elements)
	{
		element->render();
	}
}

void Pause_Menu::init()
{
	elements =
	{
		new UI_Text(renderer, Ivec(400,200), Ivec(300,150), Fvec(1.0f,1.0f), "PAUSED", "res/graphics/font.ttf", SDL_Color{255,255,255}, FILL),
		new UI_Text(renderer, Ivec(400,500), Ivec(0,0), Fvec(1.0f,1.0f), "Press enter to continue", "res/graphics/font.ttf", SDL_Color{255,255,255}, NORMAL)
	};
	elements[0]->set_origin(elements[0]->get_size()/2);
	elements[1]->set_origin(elements[1]->get_size()/2);
}

void Pause_Menu::clear()
{
	for(UI_Base* element : elements)
	{
		delete element;
	}
	elements.clear();
}

void Pause_Menu::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RETURN:
				{
					Game::toggle_pause();
				}
			}
		}
	}
}
