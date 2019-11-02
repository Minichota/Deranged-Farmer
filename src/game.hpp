#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "renderable.hpp"
#include "game-state.hpp"
#include "pause-menu.hpp"

#define STATE_COUNT 2

class Game {
	public:
	Game();
	~Game();

	void run();

	static void increment_state();
	static void set_state(int state);
	static void toggle_pause();
	static void close();

	private:
	void update();
	void render();

	void handle_event(SDL_Event event);

	private:
	static SDL_Window* window;
	static SDL_Renderer* renderer;

	static bool closed;
	static bool paused;

	static std::vector<Game_State*> game_states;
	static Pause_Menu* pause;
	static int state;
};
