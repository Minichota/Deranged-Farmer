#include "game-state.hpp"

Game_State::Game_State(SDL_Renderer* renderer) : Renderable(renderer)
{
}

Game_State::~Game_State()
{
	clear();
}

void Game_State::update()
{
	for(UI_Base* x : elements)
	{
		x->update();
	}
}

void Game_State::render()
{
	for(UI_Base* x : elements)
	{
		x->render();
	}
}

void Game_State::clear()
{
	for(UI_Base* x : elements)
	{
		delete x;
	}
	elements.clear();
}

void Game_State::handle_event(const SDL_Event& event)
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
