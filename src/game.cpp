#include <cassert>
#include <fstream>
#include <iostream>

#include "game.hpp"
#include "main-menu.hpp"
#include "level.hpp"
#include "pause-menu.hpp"
#include "settings.hpp"
#include "interpolators.hpp"

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

std::string Game::read_file(const char* file_path)
{
	// load settings
	std::ifstream read(file_path);
	if(!read)
	{
		std::cout << "failed to read file" << std::endl;
	}
	std::string buffer(std::istreambuf_iterator<char>(read), {});
	read.close();
	return buffer;
}

void Game::save_settings(const char* file_path, std::vector<std::string> names, std::vector<int*> values)
{
	std::ofstream write(file_path);
	if(!write)
	{
		std::cout << "failed to open file to write" << std::endl;
	}
	for(size_t i = 0; i < names.size(); i++)
	{
		write << names[i]+" = "+std::to_string(*values[i])+"\n";
	}
	write.close();
}

void parse_file(std::string buffer, std::vector<std::string> names, std::vector<int*> values)
{
	// TODO make this actually good
	std::string data;
	bool begin_parse = false;
	for(size_t i = 0; i < names.size(); i++)
	{
		size_t pos = buffer.find(names[i]);
		if(pos != std::string::npos)
		{
			bool cont = true;
			for(size_t j = pos; j < buffer.size(); j++)
			{
				if(!cont)
					break;
				switch(buffer[j])
				{
					case '=':
					{
						begin_parse = true;
					} break;
					case '\n':
					{
						// done
						if(begin_parse)
						{
							*values[i] = std::stoi(data);
							begin_parse = false;
							data.clear();
							cont = false;
						}
					} break;
					default:
					{
						if(begin_parse && buffer[j] != ' ')
						{
							data.push_back(buffer[j]);
						}
					} break;
				}
			}
		}
	}
}

void Game::run()
{
	std::string settings_data = read_file("res/save/settings.txt");
	std::vector<std::string> setting_names = { "volume", "iq" };

	parse_file(settings_data, setting_names, Settings::all);

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
	// TODO create struct to store data with it's name
	save_settings("res/save/settings.txt", setting_names, Settings::all);
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
