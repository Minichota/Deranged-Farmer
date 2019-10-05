#include <iostream>
#include <SDL2/SDL_ttf.h>
#include "game.hpp"

int main(){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "error" << std::endl;
	}
	if(TTF_Init() != 0)
	{
		std::cout << "error in loading ttf" << std::endl;
	}
	Game game = Game();
	game.run();
	return 0;
}
