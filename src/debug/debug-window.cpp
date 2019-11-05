#include <iostream>

#include "debug-window.hpp"
#include "error.hpp"

#define MAX_SCROLL 1600
#define FLOAT_ACCURACY 3

Debug_Window::Debug_Window(SDL_Renderer* renderer):
Renderable(renderer)
{
	this->inner_selection = -1;
	this->outer_selection = -1;
	this->pos = Ivec(600,0);
	scroll_pos = 0;

	font = TTF_OpenFont("res/graphics/font.ttf", 16);
	Error(!font, {"failed to load font", SDL_GetError()});
}

Debug_Window::~Debug_Window()
{
}

void Debug_Window::update()
{
}

void Debug_Window::render()
{
	// background blending
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
	SDL_Rect x = {pos.x,pos.y,200,608};
	SDL_RenderFillRect(renderer, &x);
	inner_rects.clear();
	outer_rects.clear();
	Ivec draw_pos = {this->pos.x, this->pos.y - scroll_pos};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// outer layer
	for(size_t i = 0; i < to_render.size(); i++)
	{
		SDL_Surface* surface = TTF_RenderText_Solid(font, to_render[i].name.c_str(), SDL_Color{255,255,255,255});
		SDL_Texture* output = SDL_CreateTextureFromSurface(renderer, surface);
		Ivec tex_size;
		SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect size_rect =
		{
			draw_pos.x,
			draw_pos.y,
			tex_size.x,
			tex_size.y
		};
		outer_rects.push_back(size_rect);
		SDL_RenderCopy(renderer, output, NULL, &size_rect);
		SDL_DestroyTexture(output);
		SDL_FreeSurface(surface);
		draw_pos.y += tex_size.y;
	}
	draw_pos = pos;
	// inner layer
	if(outer_selection >= 0)
	{
		std::cout << outer_selection << "  " << inner_selection << std::endl;
		for(size_t i = 0; i < to_render[outer_selection].values.size(); i++)
		{
			std::string x = std::to_string(to_render[outer_selection].values[i].x);
			x.erase(x.find_last_not_of('0') + FLOAT_ACCURACY, std::string::npos);
			std::string y = std::to_string(to_render[outer_selection].values[i].y);
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
			inner_rects.push_back(size_rect);
			SDL_RenderCopy(renderer, output, NULL, &size_rect);
			SDL_DestroyTexture(output);
			SDL_FreeSurface(surface);
			draw_pos.y += tex_size.y;
		}
	}

	to_render.clear();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void Debug_Window::handle_event(SDL_Event event)
{
	if(active)
	{
		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				Ivec mouse_position = Ivec(event.button.x, event.button.y);
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						select(mouse_position);
					} break;
				}
			} break;
			case SDL_MOUSEWHEEL:
			{
				if(event.wheel.y > 0)
				{
					// scroll up
					this->scroll_pos -= 100;
					if(scroll_pos < 0)
					{
						scroll_pos = 0;
					}
				}
				if(event.wheel.y < 0)
				{
					// scroll down
					this->scroll_pos += 100;
					if(scroll_pos > MAX_SCROLL)
					{
						scroll_pos = MAX_SCROLL;
					}
				}
			} break;
		}
	}
}

void Debug_Window::push_render(std::string name_repr, std::vector<Fvec> values)
{
	to_render.push_back(Debug_Element{name_repr, values});
}

void Debug_Window::toggle()
{
	this->active = !this->active;
}

void Debug_Window::select(Ivec pos)
{
	for(size_t i = 0; i < outer_rects.size(); i++)
	{
		if(pos.x > outer_rects[i].x &&
		   pos.y > outer_rects[i].y &&
		   pos.x < outer_rects[i].x + outer_rects[i].w &&
		   pos.y < outer_rects[i].y + outer_rects[i].h)
		{
			outer_selection = i;
			return;
		}
	}
	for(size_t i = 0; i < inner_rects.size(); i++)
	{
		if(pos.x > inner_rects[i].x &&
		   pos.y > inner_rects[i].y &&
		   pos.x < inner_rects[i].x + inner_rects[i].w &&
		   pos.y < inner_rects[i].y + inner_rects[i].h)
		{
			inner_selection = i;
			return;
		}
	}
	inner_selection = -1;
	outer_selection = -1;
}
