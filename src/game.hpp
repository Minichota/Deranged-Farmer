#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "renderable.hpp"
#include "game-state.hpp"

#define STATE_COUNT 1

class Game {
	public:
	Game();
	~Game();

	void run();

	private:
	void update();
	void render();

	void increment_state();
	void set_state(int state);

	void handle_event(SDL_Event event);

	private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* world_texture;

	bool closed;

	std::vector<GameState*> game_states;
	int state;
};
