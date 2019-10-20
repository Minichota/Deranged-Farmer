#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "ui-text.hpp"

UI_Text::UI_Text(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::string text, std::string font_path, SDL_Color font_color):
UI_Base(renderer, pos, size, scale, font_color)
{
	this->scale = scale;
	this->tex_size = Ivec(0,0);

	this->text = text;
	this->prev_text = "";
	this->font_path = font_path;

	this->font = TTF_OpenFont(font_path.c_str(), 24);
	if(!font)
	{
		std::cout << "failed to create font face" << std::endl;
	}
	this->font_color = font_color;
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
	if(this->text != this->prev_text)
	{
		SDL_Surface* new_surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
		output = SDL_CreateTextureFromSurface(renderer, new_surface);
		SDL_QueryTexture(output, NULL, NULL, &tex_size.x, &tex_size.y);
		this->prev_text = this->text;
		SDL_FreeSurface(new_surface);
	}
	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_Rect position = {(int)(pos.x/scale.x), (int)(pos.y / scale.y), tex_size.x, tex_size.y};
	SDL_RenderCopy(renderer, output, NULL, &position);
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
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
