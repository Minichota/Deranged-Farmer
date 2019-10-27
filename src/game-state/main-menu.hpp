#include <vector>

#include "game-state.hpp"
#include "vectors.hpp"

class Main_Menu : public Game_State
{
	public:
	Main_Menu(SDL_Renderer* renderer);

	void init();

	void handle_event(SDL_Event event);
};
