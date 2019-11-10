#include <iostream>

#include "ui-image.hpp"
#include "error.hpp"
#include "util.hpp"

UI_Image::UI_Image(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Fill_Type fill_type, std::string file_path):
UI_Base(renderer, pos, size, scale, SDL_Color{})
{
	this->fill_type = fill_type;
	{
		this->texture = IMG_LoadTexture(renderer, file_path.c_str());
		Error texture_ld(!texture, {"failed to load image texture"});
	}
	switch(fill_type)
	{
		case FILL:
		{
		} break;
		case NORMAL:
		{
			SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
		} break;
		case WRAPPED:
		{
		} break;
	}

}

UI_Image::~UI_Image()
{
}

void UI_Image::update()
{
	output_rect = SDL_Rect{get_pos().x,
						   get_pos().y,
						   size.x,
						   size.y};
}

void UI_Image::render()
{
	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_RenderCopy(renderer, texture, NULL, &output_rect);
	clear_render_settings(renderer);
}
