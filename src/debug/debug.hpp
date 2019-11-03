#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <SDL2/SDL_ttf.h>
#include <vector>

#include "vectors.hpp"

namespace Debug
{
	void init();
	void render_debug_text(SDL_Renderer* renderer, Ivec pos, std::vector<Ivec> x = {});
	void toggle();
	extern TTF_Font* font;
	extern bool active;
};
#endif
