#include <iostream>
#include <algorithm>
#include <cctype>

#include "debug-window.hpp"
#include "error.hpp"
#include "util.hpp"
#include "sized.hpp"

#define MAX_SCROLL 1600

Debug_Window::Debug_Window(SDL_Renderer* renderer):
Renderable(renderer),
text_input(renderer, Ivec(400,400), Ivec(100,100), Fvec(1.0f, 1.0f), "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL)
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
	text_input.update();
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
	SDL_Surface* surface;
	for(size_t i = 0; i < to_render.size(); i++)
	{
		if(to_render[i].texture == nullptr)
		{
			surface = TTF_RenderText_Solid(font, to_render[i].name.c_str(), SDL_Color{255,255,255,255});
			to_render[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
		Ivec tex_size;
		SDL_QueryTexture(to_render[i].texture, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect size_rect =
		{
			draw_pos.x,
			draw_pos.y,
			tex_size.x,
			tex_size.y
		};
		outer_rects.push_back(size_rect);
		SDL_RenderCopy(renderer, to_render[i].texture, NULL, &size_rect);
		draw_pos.y += tex_size.y;
	}

	// inner layer
	draw_pos = pos;
	if(outer_selection >= 0)
	{
		for(size_t i = 0; i < to_render[outer_selection].values.size(); i++)
		{
			std::string x = std::to_string(*to_render[outer_selection].values[i]);
			remove_zeros(x);

			surface = TTF_RenderText_Solid(font, x.c_str(), SDL_Color{255,255,255,255});
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
			Ivec tex_size;
			SDL_QueryTexture(texture, NULL, NULL, &tex_size.x, &tex_size.y);
			SDL_Rect size_rect =
			{
				draw_pos.x + 50,
				draw_pos.y,
				tex_size.x,
				tex_size.y
			};
			inner_rects.push_back(size_rect);
			SDL_RenderCopy(renderer, texture, NULL, &size_rect);
			SDL_DestroyTexture(texture);
			draw_pos.y += tex_size.y;
		}
		Ivec tex_size;
		SDL_QueryTexture(to_render[outer_selection].texture, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect selected_outline = {pos.x, pos.y + (-scroll_pos + 19 * outer_selection), tex_size.x, tex_size.y};
		if(selected_outline.y >= 608)
		{
			scroll_pos += selected_outline.y;
		}
		while(pos.y + (-scroll_pos + 19 * outer_selection) < 0)
		{
			scroll_pos -= 19;
		}
		SDL_RenderDrawRect(renderer, &selected_outline);

		Sized<float>* entity_dimensions = to_render[outer_selection].address;
		if(entity_dimensions != nullptr)
		{
			SDL_Rect entity_outline =
			{
				(int)std::round(entity_dimensions->get_pos().x/3),
				(int)std::round(entity_dimensions->get_pos().y/3),
				(int)std::round(entity_dimensions->get_size().x/3),
				(int)std::round(entity_dimensions->get_size().y/3)
			};
			SDL_RenderSetScale(renderer, 3.0f, 3.0f);
			SDL_RenderDrawRect(renderer, &entity_outline);
			SDL_RenderSetScale(renderer, 1.0f, 1.0f);
		}
	}
	if(inner_selection >= 0)
	{
		Ivec tex_size;
		SDL_Rect selected_box_2 = {pos.x + 50, pos.y + 19 * inner_selection, 5, 5};
		SDL_RenderDrawRect(renderer, &selected_box_2);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	text_input.render();
}

void Debug_Window::clear()
{
	text_input.set_string("");
	outer_selection = -1;
	inner_selection = -1;
	to_render.clear();
	active = false;
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
			case SDL_KEYDOWN:
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_BACKSPACE:
					{
						text_input.handle_event(event);
					} break;
					case SDLK_RETURN:
					{
						if(text_input.get_string().size() > 0)
						{
							*to_render[outer_selection].values[inner_selection] = atof(text_input.get_string().c_str());
							set_string(*to_render[outer_selection].values[inner_selection]);
						}
					} break;
					case SDLK_j:
					{
						// down
						if(keys[SDL_SCANCODE_LCTRL])
						{
							outer_selection++;
							if((size_t)outer_selection > to_render.size() - 1)
							{
								outer_selection = 0;
							}
							inner_selection = -1;
							set_string("");
						}
						else if(outer_selection >= 0)
						{
							inner_selection++;
							if((size_t)inner_selection > to_render[outer_selection].values.size() - 1)
							{
								inner_selection = 0;
							}
							set_string(*to_render[outer_selection].values[inner_selection]);
						}
					} break;
					case SDLK_k:
					{
						// up
						if(keys[SDL_SCANCODE_LCTRL])
						{
							outer_selection--;
							if(outer_selection < 0)
							{
								outer_selection = to_render.size() - 1;
							}
							inner_selection = -1;
							set_string("");
						}
						else if(outer_selection >= 0)
						{
							inner_selection--;
							if(inner_selection < 0)
							{
								inner_selection = to_render[outer_selection].values.size() - 1;
							}
							set_string(*to_render[outer_selection].values[inner_selection]);
						}
					} break;
				}
			} break;
			case SDL_TEXTINPUT:
			{
				if((isdigit(event.text.text[0]) || event.text.text[0] == '.') && inner_selection >= 0)
				{
					text_input.handle_event(event);
				}
			} break;
		}
	}
}

void Debug_Window::push_render(Sized<float>* address, std::string name_repr, std::vector<float*> values)
{
	Debug_Element maybe{address, name_repr, values};
	if(!(std::find_if(to_render.begin(), to_render.end(), [&cr = maybe](const Debug_Element& cr2) -> bool {return cr2.address == cr.address;}) != to_render.end()))
	{
		to_render.push_back(Debug_Element{address, name_repr, values});
	}
}

void Debug_Window::toggle()
{
	this->active = !this->active;
	if(!active)
	{
		clear();
	}
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
			set_string(*to_render[outer_selection].values[inner_selection]);
			return;
		}
	}
	inner_selection = -1;
	outer_selection = -1;

	text_input.set_string("");
}

void Debug_Window::set_string(std::string input)
{
	remove_zeros(input);
	text_input.set_string(input);
}

void Debug_Window::set_string(float input)
{
	std::string str = std::to_string(input);
	remove_zeros(str);
	text_input.set_string(str);
}

void Debug_Window::remove_zeros(std::string& input)
{
	char* c = &input.back();
	while(*c == '0')
	{
		input.pop_back();
		c--;
	}
	// remove decimal point
	if(*c == '.')
	{
		input.pop_back();
	}
}
