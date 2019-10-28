#include <cassert>
#include <fstream>
#include <iostream>

#include "game.hpp"
#include "main-menu.hpp"
#include "level.hpp"
#include "pause-menu.hpp"
#include "settings.hpp"
#include "interpolators.hpp"
#include "io.hpp"

// static variables
int Game::state;
std::vector<Game_State*> Game::game_states;
Pause_Menu* Game::pause;
bool Game::paused;

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
	std::string settings_data = read("res/save/settings.txt");
	parse(settings_data, '=', Settings::all);

	game_states =
	{
		new Main_Menu(renderer),
		new Level(renderer, "", "")
	};

	this->pause = new Pause_Menu(renderer);
	set_state(0);

	closed = false;
	paused = false;
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

		update_interpolators();
		update();
		render();

		SDL_RenderPresent(renderer);
		SDL_Delay(1000.0f/144.0f);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	write("res/save/settings.txt", Settings::all);
}

void Game::update()
{
	assert(state >= 0 && state < STATE_COUNT);
	if(paused)
	{
		pause->update();
	}
	else
	{
		game_states[this->state]->update();
	}
}

void Game::render()
{
	assert(state >= 0 && state < STATE_COUNT);
		game_states[this->state]->render();
	if(paused)
	{
		pause->render();
	}
}

void Game::increment_state()
{
	// clear previous state
	game_states[Game::state]->clear();
	Game::state++;
	assert(state < STATE_COUNT);
	// initialize new state
	clear_interpolators();
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
	clear_interpolators();
	game_states[Game::state]->init();
}

void Game::toggle_pause()
{
	assert(state != 0);
	if((paused = !paused))
	{
		pause->init();
	}
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
			if(paused)
			{
				pause->handle_event(event);
			}
			else
			{
				game_states[this->state]->handle_event(event);
			}
		} break;
	}
}
