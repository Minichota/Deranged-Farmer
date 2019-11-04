#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <SDL2/SDL_ttf.h>
#include <vector>

#include "vectors.hpp"

typedef struct
{
	std::string name;
	std::vector<Ivec> renders;
} Debug_Element;

namespace Debug
{
	void init();
	void render_debug_text(SDL_Renderer* renderer, Ivec pos);
	void toggle();
	void push_render(std::string name, std::vector<Ivec> render);
	void open_selection(Ivec pos);

	extern int selection;

	extern std::vector<Debug_Element> to_render;
	extern std::vector<SDL_Rect> rects;
	extern TTF_Font* font;
	extern bool active;
};
#endif
