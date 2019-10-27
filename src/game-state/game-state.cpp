#include "game-state.hpp"

Game_State::Game_State(SDL_Renderer* renderer):
Renderable(renderer)
{
}

Game_State::~Game_State()
{
	clear();
}

void Game_State::update()
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->update();
	}
}

void Game_State::render()
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		elements[i]->render();
	}
}

void Game_State::clear()
{
	for(size_t i = 0; i < elements.size(); i++)
	{
		delete elements[i];
	}
	elements.clear();
}

void Game_State::handle_event(SDL_Event event)
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
