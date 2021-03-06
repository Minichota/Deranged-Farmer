#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "audio.hpp"
#include "error.hpp"
#include "game.hpp"

int main()
{
	{
		Error(SDL_Init(SDL_INIT_EVERYTHING) < 0,
			  { "Failed to initialize SDL", SDL_GetError() }, true);
		Error(SDL_Init(SDL_INIT_VIDEO) < 0,
			  { "Failed to initialize SDL_video", SDL_GetError() }, true);
		Error(TTF_Init() < 0,
			  { "Failed to initialize SDL_ttf", SDL_GetError() }, true);
		int imgFlags = IMG_INIT_PNG;
		Error(!(IMG_Init(imgFlags) & imgFlags),
			  { "Failed to initialize SDL_image: ", SDL_GetError() }, true);
	}
	audio::init();
	Game game = Game();
	game.run();
	return 0;
}
