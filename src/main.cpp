#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "game.hpp"
#include "error.hpp"

int main(){
	{
		Error sdl(SDL_Init(SDL_INIT_EVERYTHING) < 0, {"Failed to initialize SDL", SDL_GetError()}, true);
		Error sdl_vid(SDL_Init(SDL_INIT_VIDEO) < 0, {"Failed to initialize SDL_video", SDL_GetError()}, true);
		Error sdl_ttf(TTF_Init() < 0, {"Failed to initialize SDL_ttf", SDL_GetError()}, true);
		int imgFlags = IMG_INIT_PNG;
		Error sdl_img(!(IMG_Init(imgFlags) & imgFlags), {"Failed to initialize SDL_image: ", SDL_GetError()}, true);
	}
	Game game = Game();
	game.run();
	return 0;
}
