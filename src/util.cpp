#include "util.hpp"

void clear_render_settings(SDL_Renderer* const renderer)
{
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderTarget(renderer, NULL);
}
unsigned char* keys;
