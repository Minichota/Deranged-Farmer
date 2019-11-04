#include <cmath>
#include <string>

#include "debug.hpp"
#include "error.hpp"
#include "vectors.hpp"

#define FLOAT_ACCURACY 3

bool Debug::active = false;
TTF_Font* Debug::font = nullptr;
std::vector<Debug_Element> Debug::to_render = {};
std::vector<SDL_Rect> Debug::rects = {};
int Debug::selection = 0;

void Debug::init()
{
	Debug::font = TTF_OpenFont("res/graphics/font.ttf", 16);
	Error(!Debug::font, {"failed to load font", SDL_GetError()});
}

void Debug::render_debug_text(SDL_Renderer* renderer, Ivec pos)
{
	rects.clear();
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// outer layer
	Ivec draw_pos = pos;
	for(size_t i = 0; i < to_render.size(); i++)
	{
		std::string output_str = to_render[i].name;
		SDL_Surface* surface = TTF_RenderText_Solid(font, output_str.c_str(), SDL_Color{255,255,255,255});
		Ivec tex_size;
		SDL_Texture* output = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect size_rect =
		{
			draw_pos.x,
			draw_pos.y,
			tex_size.x,
			tex_size.y
		};
		rects.push_back(size_rect);
		SDL_RenderCopy(renderer, output, NULL, &size_rect);
		SDL_DestroyTexture(output);
		SDL_FreeSurface(surface);
		draw_pos.y += tex_size.y;
	}
	draw_pos = pos;
	// inner layer
	if(selection >= 0)
	{
		for(size_t i = 0; i < to_render[selection].renders.size(); i++)
		{
			std::string x = std::to_string(to_render[selection].renders[i].x);
			x.erase(x.find_last_not_of('0') + FLOAT_ACCURACY, std::string::npos);
			std::string y = std::to_string(to_render[selection].renders[i].y);
			y.erase(y.find_last_not_of('0') + FLOAT_ACCURACY, std::string::npos);
			std::string output_str = x + " " + y;
			SDL_Surface* surface = TTF_RenderText_Solid(font, output_str.c_str(), SDL_Color{255,255,255,255});
			Ivec tex_size;
			SDL_Texture* output = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
			SDL_Rect size_rect =
			{
				draw_pos.x + 50,
				draw_pos.y,
				tex_size.x,
				tex_size.y
			};
			rects.push_back(size_rect);
			SDL_RenderCopy(renderer, output, NULL, &size_rect);
			SDL_DestroyTexture(output);
			SDL_FreeSurface(surface);
			draw_pos.y += tex_size.y;
		}
	}

	to_render.clear();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Debug::toggle()
{
	active = !active;
}

void Debug::push_render(std::string name, std::vector<Fvec> render)
{
	to_render.push_back(Debug_Element{name, render});
}

void Debug::open_selection(Ivec pos)
{
	for(size_t i = 0; i < rects.size(); i++)
	{
		if(pos.x > rects[i].x &&
		   pos.y > rects[i].y &&
		   pos.x < rects[i].x + rects[i].w &&
		   pos.y < rects[i].y + rects[i].h)
		{
			selection = i;
			return;
		}
	}
	selection = -1;
}
