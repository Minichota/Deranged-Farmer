#include <SDL2/SDL.h>
#include <SDL2/SDL_system.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "renderable.hpp"

class Game {
	public:
	Game();
	~Game();

	void run();

	private:
	void update();
	void render();

	void handle_event(SDL_Event event);

	private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* world_texture;

	bool closed;
};
