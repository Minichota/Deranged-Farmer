#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "ui-text.hpp"

UI_Text::UI_Text(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::string text, std::string font_path, SDL_Color font_color):
UI_Base(renderer, pos, size, scale, font_color)
{
	this->text = text;
	this->prev_text = "";
	this->prev_scale = Fvec(1.0f,1.0f);
	this->font_path = font_path;

	this->font = TTF_OpenFont(font_path.c_str(), 24);
	if(!font)
	{
		std::cout << "failed to create font face" << std::endl;
	}
	this->font_color = font_color;

	SDL_Surface* new_surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
	output = SDL_CreateTextureFromSurface(renderer, new_surface);
	SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
	this->prev_text = this->text;
	SDL_FreeSurface(new_surface);
}

UI_Text::~UI_Text()
{
	this->text.clear();
	this->prev_text.clear();
	TTF_CloseFont(this->font);
}

void UI_Text::update()
{
	this->actual_size = this->size;
}

void UI_Text::render()
{
	if(this->text != this->prev_text || this->scale != this->prev_scale)
	{
		reload_texture();
	}
	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_Rect position = {get_pos().x, get_pos().y, tex_size.x, tex_size.y};
	SDL_RenderCopy(renderer, output, NULL, &position);
	SDL_RenderSetScale(renderer, 1.0f,1.0f);
}

void UI_Text::reload_texture()
{
	SDL_Surface* new_surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
	output = SDL_CreateTextureFromSurface(renderer, new_surface);
	SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
	this->prev_text = this->text;
	this->prev_scale = this->scale;
	SDL_FreeSurface(new_surface);
}

void UI_Text::set_text(std::string text)
{
	this->text = text;
}

void UI_Text::append_text(std::string text)
{
	this->text.append(text);
}

std::string UI_Text::get_text()
{
	return this->text;
}

Ivec& UI_Text::get_size()
{
	return this->tex_size;
}

void UI_Text::set_font_size(int font_size)
{
	TTF_CloseFont(font);
	TTF_OpenFont(font_path.c_str(), font_size);
	reload_texture();
}
