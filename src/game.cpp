#include <cassert>
#include <fstream>
#include <iostream>

#include "game.hpp"
#include "audio.hpp"
#include "main-menu.hpp"
#include "level.hpp"
#include "pause-menu.hpp"
#include "settings.hpp"
#include "interpolators.hpp"
#include "io.hpp"
#include "util.hpp"
#include "debug-window.hpp"

// static variables
int Game::state;
Game_State* Game::game_states[STATE_COUNT];
Pause_Menu* Game::pause;
bool Game::paused = false;
bool Game::closed = false;
Debug_Window* Game::debug;

Game::Game()
{
	window = SDL_CreateWindow("Deranged Farmer",
		   					   SDL_WINDOWPOS_CENTERED,
		   					   SDL_WINDOWPOS_CENTERED,
		   					   800,
		   					   608,
		   					   SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetWindowResizable(window, SDL_FALSE);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::run()
{
	std::string settings_data = read("res/save/settings.txt");
	parse(settings_data, '=', Settings::all);
 	Game::debug = new Debug_Window(renderer);
	game_states[0] = new Main_Menu(renderer);
	Level* level = new Level(renderer, "res/map/entities.dat", "res/map/test_map.dat", "res/graphics/tile_map.png");
	game_states[1] = level;
	debug->set_level(level);

	this->pause = new Pause_Menu(renderer);
	pause->init();
	set_state(0);

	closed = false;
	paused = false;
	while(!closed)
	{
		SDL_Event event;
		keys = (unsigned char*)SDL_GetKeyboardState(NULL);
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
	write_settings("res/save/settings.txt", Settings::all);
}

void Game::update()
{
	assert(state >= 0 && state < STATE_COUNT);
	if(debug->active)
	{
		debug->update();
	}
	if(paused)
	{
		pause->update();
	}
	else
	{
		game_states[this->state]->update();
	}
	audio::update();
}

void Game::render()
{
	assert(state >= 0 && state < STATE_COUNT);
	game_states[this->state]->render();
	if(paused)
	{
		pause->render();
	}
	if(debug->active)
	{
		debug->render();
	}
}

void Game::increment_state()
{
	// clear previous state
	game_states[Game::state]->clear();
	paused = false;
	debug->clear();
	Game::state++;
	assert(state < STATE_COUNT);
	// initialize new state
	clear_interpolators();
	pause->init();
	game_states[Game::state]->init();
}

void Game::set_state(int state)
{
	assert(state >= 0 && state < STATE_COUNT);
	// clear previous state
	game_states[Game::state]->clear();
	paused = false;
	debug->clear();
	Game::state = state;
	// initialize new state
	clear_interpolators();
	pause->init();
	game_states[Game::state]->init();
}

void Game::toggle_pause()
{
	assert(state != 0);
	paused = !paused;
	audio::toggle_pause();
}

void Game::close()
{
	write_settings("res/save/settings.txt", Settings::all);
	exit(-1);
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
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_F12:
				{
					if(this->state != 0)
					{
						debug->toggle();
					}
				} break;
				case SDLK_F4:
				{
					// bypass so save can be done in debug mode
					game_states[this->state]->handle_event(event);
				} break;
			}
		}
		default:
		{
			if(debug->active)
			{
				debug->handle_event(event);
			}
			else if(paused)
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
