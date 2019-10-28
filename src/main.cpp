#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "game.hpp"

int main(){
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "error" << std::endl;
	}
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "error" << std::endl;
	}
	if(TTF_Init() < 0)
	{
		std::cout << "error in loading ttf" << std::endl;
	}
	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cout << "error in loading image" << std::endl;
	}
	Game game = Game();
	game.run();
	return 0;
}
