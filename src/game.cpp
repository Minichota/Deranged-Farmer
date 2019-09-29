#include "game.hpp"

Game::Game()
{
	window = SDL_CreateWindow("Deranged Farmer",
		   					   SDL_WINDOWPOS_CENTERED,
		   					   SDL_WINDOWPOS_CENTERED,
		   					   1000,
		   					   1000,
		   					   SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

Game::~Game()
{
}

void Game::run()
{
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
		SDL_Delay(1000.0f/60.0f);
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(world_texture);
}

void Game::update()
{
}

void Game::render()
{

	const SDL_Rect world_out = SDL_Rect{0, 0, 1000, 1000};
	SDL_RenderCopy(renderer, world_texture, &world_out, &world_out);
}

void Game::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_QUIT:
		{
			closed = true;
		} break;
	}
}
