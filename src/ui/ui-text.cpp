#include <SDL2/SDL_ttf.h>
#include <iostream>

#include "ui-text.hpp"

UI_Text::UI_Text(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::string text, std::string font_path, SDL_Color font_color):
UI_Base(renderer, pos, size, scale)
{
	this->scale = scale;

	this->text = text;
	this->prev_text = "";
	this->font_path = font_path;

	std::cout << font_path << std::endl;
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
}

// TODO implement ui-text scaling
void UI_Text::update()
{
	this->actual_size = this->size * this->scale;
}

void UI_Text::render()
{
	if(this->text != this->prev_text)
	{
		SDL_Surface* new_surface = TTF_RenderText_Solid(font, text.c_str(), font_color);
		output = SDL_CreateTextureFromSurface(renderer, new_surface);
		this->prev_text = this->text;
	}
	SDL_Rect position = {pos.x, pos.y, actual_size.x, actual_size.y};
	SDL_RenderCopy(renderer, output, NULL, &position);
}
