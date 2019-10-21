#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "renderable.hpp"
#include "game-state.hpp"

#define STATE_COUNT 3

class Game {
	public:
	Game();
	~Game();

	void run();

	static void increment_state();
	static void set_state(int state);

	private:
	void update();
	void render();

	void handle_event(SDL_Event event);

	private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool closed;

	static std::vector<Game_State*> game_states;
	static int state;
};
