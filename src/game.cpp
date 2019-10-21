#include <cassert>
#include <iostream>

#include "game.hpp"
#include "main-menu.hpp"
#include "level.hpp"
#include "pause-menu.hpp"

// static variables
int Game::state;
std::vector<Game_State*> Game::game_states;

Game::Game()
{
	window = SDL_CreateWindow("Deranged Farmer",
		   					   SDL_WINDOWPOS_CENTERED,
		   					   SDL_WINDOWPOS_CENTERED,
		   					   800,
		   					   600,
		   					   SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetWindowResizable(window, SDL_FALSE);
}

Game::~Game()
{
}

void Game::run()
{
	// create state
	game_states =
	{
		new Main_Menu(renderer),
		new Pause_Menu(renderer),
		new Level(renderer, "", "")
	};
	set_state(0);

	closed = false;
	while(!closed)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event) > 0)
		{
			handle_event(event);
			SDL_UpdateWindowSurface(window);
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		update();
		render();

		SDL_RenderPresent(renderer);
		SDL_Delay(1000.0f/144.0f);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::update()
{
	assert(state >= 0 && state < STATE_COUNT);
	game_states[this->state]->update();
}

void Game::render()
{
	assert(state >= 0 && state < STATE_COUNT);
	game_states[this->state]->render();
}

void Game::increment_state()
{
	// clear previous state
	game_states[Game::state]->clear();
	Game::state++;
	assert(state < STATE_COUNT);
	// initialize new state
	game_states[Game::state]->init();
}

void Game::set_state(int state)
{
	assert(state >= 0 && state < STATE_COUNT);
	// clear previous state
	if(game_states.size() > 1)
	{
		game_states[Game::state]->clear();
	}
	Game::state = state;
	// initialize new state
	game_states[Game::state]->init();
}

void Game::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_QUIT:
		{
			// user closes window
			closed = true;
		} break;
		default:
		{
			game_states[this->state]->handle_event(event);
		} break;
	}
}
