#include <iostream>
#include "game.hpp"

int main(){
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "error" << std::endl;
	}
	Game game = Game();
	game.run();
	return 0;
}
