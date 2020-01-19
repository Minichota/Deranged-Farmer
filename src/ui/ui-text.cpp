#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "error.hpp"
#include "ui-text.hpp"
#include "util.hpp"

UI_Text::UI_Text(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale,
				 std::string text, std::string font_path, SDL_Color font_color,
				 Fill_Type type) :
UI_Base(renderer, pos, size, scale, font_color)
{
	this->type = type;
	this->text = text;
	this->prev_text = "";
	this->font_path = font_path;

	{
		this->font = TTF_OpenFont(font_path.c_str(), 24);
		Error font_ld(!font, { "failed to create font face" });
	}

	this->font_color = font_color;
	this->output = nullptr;
	reload_texture();
	this->font_height = TTF_FontHeight(font);
}

UI_Text::~UI_Text()
{
	this->text.clear();
	this->prev_text.clear();
	TTF_CloseFont(this->font);
	SDL_DestroyTexture(output);
}

void UI_Text::update()
{
	this->actual_size = this->size;
}

void UI_Text::render()
{
	if(this->text != this->prev_text || !output)
	{
		reload_texture();
	}

	SDL_SetTextureAlphaMod(output, color.a);
	switch(type)
	{
		case WRAPPED:
		case NORMAL:
		{
			SDL_RenderSetScale(renderer, scale.x, scale.y);
			SDL_Rect position = { get_pos().x + camera.x - 400,
								  get_pos().y + camera.y - 304, tex_size.x,
								  tex_size.y };
			SDL_RenderCopy(renderer, output, NULL, &position);
		}
		break;
		case FILL:
		{
			SDL_Rect position = {
				(int)std::round(pos.x -
								origin.x * (size.x / (float)tex_size.x) +
								camera.x - 400),
				(int)std::round(pos.y -
								origin.y * (size.y / (float)tex_size.y) +
								camera.y - 304),
				size.x, size.y
			};
			SDL_RenderCopy(renderer, output, NULL, &position);
		}
		break;
	}
	clear_render_settings(renderer);
}

void UI_Text::reload_texture()
{
	SDL_Surface* new_surface = nullptr;
	switch(type)
	{
		case NORMAL:
		case FILL:
		{
			new_surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
		}
		break;
		case WRAPPED:
		{
			new_surface = TTF_RenderText_Blended_Wrapped(font, text.c_str(),
														 font_color, size.x);
		}
		break;
		default:
		{
			Error(true,
				  { "You somehow set the surface to a non-existant type?" });
		}
		break;
	}
	if(output != nullptr)
	{
		SDL_DestroyTexture(output);
	}
	output = SDL_CreateTextureFromSurface(renderer, new_surface);
	SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
	this->prev_text = this->text;
	SDL_FreeSurface(new_surface);
}

void UI_Text::set_text(std::string text)
{
	this->text = text;
	if(this->text != this->prev_text)
	{
		reload_texture();
	}
}

void UI_Text::append_text(std::string text)
{
	this->text.append(text);
}

void UI_Text::prepend_text(std::string text)
{
	this->text.insert(0, text);
}

void UI_Text::clear()
{
	this->text.clear();
	if(output != nullptr)
	{
		SDL_DestroyTexture(output);
		output = nullptr;
	}
}

std::string UI_Text::get_text()
{
	return this->text;
}

Ivec& UI_Text::get_size()
{
	return this->tex_size;
}

void UI_Text::set_font_size(int font_size, bool refresh)
{
	TTF_CloseFont(font);
	font = TTF_OpenFont(font_path.c_str(), font_size);
	if(refresh)
	{
		reload_texture();
	}
	this->font_height = TTF_FontHeight(font);
}

void UI_Text::set_color(const SDL_Color color, bool refresh)
{
	this->font_color = color;
	if(refresh)
	{
		reload_texture();
	}
}
