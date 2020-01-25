#include "util.hpp"

void clear_render_settings(SDL_Renderer* const renderer)
{
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderTarget(renderer, NULL);
}
Ivec map_world(Ivec pos)
{
	return Ivec(pos.x + camera.x - 400, pos.y + camera.y - 304);
}
unsigned char* keys;
Ivec camera;
