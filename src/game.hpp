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

	private:
	void update();
	void render();

	void handle_event(SDL_Event event);

	void save_settings(const char* file, std::vector<std::string> names, std::vector<int*> values);

	private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	bool closed;
	static bool paused;

	static std::vector<Game_State*> game_states;
	static Pause_Menu* pause;
	static int state;
};
