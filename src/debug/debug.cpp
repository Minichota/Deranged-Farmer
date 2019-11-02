#include <cmath>
#include <string>

#include "debug.hpp"
#include "error.hpp"

void Debug::init()
{
	Debug::font = TTF_OpenFont("res/graphics/font.ttf", 16);
	Error(!font, {"failed to load font", SDL_GetError()});
}

void Debug::render_debug_text(SDL_Renderer* renderer, Ivec pos, std::vector<Ivec> values)
{
	for(size_t i = 0; i < values.size(); i++)
	{
		std::string output_str = "x: " + std::to_string(values[i].x) + " y: " + std::to_string(values[i].y);
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
		pos.y += 16;
	}
}
