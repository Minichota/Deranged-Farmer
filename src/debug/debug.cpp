#include <cmath>
#include <string>

#include "debug.hpp"
#include "error.hpp"

bool Debug::active = false;
TTF_Font* Debug::font = nullptr;
std::vector<Ivec> Debug::to_render = {};

void Debug::init()
{
	Debug::font = TTF_OpenFont("res/graphics/font.ttf", 16);
	Error(!Debug::font, {"failed to load font", SDL_GetError()});
}

void Debug::render_debug_text(SDL_Renderer* renderer, Ivec pos)
{
	for(size_t i = 0; i < to_render.size(); i++)
	{
		std::string output_str = std::to_string(to_render[i].x) + " " + std::to_string(to_render[i].y);
		SDL_Surface* surf = TTF_RenderText_Solid(font, output_str.c_str(), SDL_Color{255,255,255,255});
		Ivec tex_size;
		SDL_Texture* output = SDL_CreateTextureFromSurface(renderer, surf);
		SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect size_rect =
		{
			pos.x,
			pos.y,
			tex_size.x,
			tex_size.y
		};
		SDL_RenderCopy(renderer, output, NULL, &size_rect);
		SDL_DestroyTexture(output);
		SDL_FreeSurface(surf);
		pos.y += tex_size.y;
	}
	to_render.clear();
}

void Debug::toggle()
{
	active = !active;
}

void Debug::push_render(std::vector<Ivec> render)
{
	for(Ivec x : render)
	{
		to_render.push_back(x);
	}
}
