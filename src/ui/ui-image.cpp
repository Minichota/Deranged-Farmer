#include <iostream>

#include "error.hpp"
#include "ui-image.hpp"
#include "util.hpp"

UI_Image::UI_Image(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale,
				   Fill_Type fill_type, std::string file_path) :
UI_Base(renderer, pos, size, scale, SDL_Color{})
{
	this->fill_type = fill_type;
	{
		this->texture = IMG_LoadTexture(renderer, file_path.c_str());
		Error texture_ld(!texture, { "failed to load image texture" });
	}
	switch(fill_type)
	{
		case FILL:
		{
		}
		break;
		case NORMAL:
		{
			SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
		}
		break;
		case WRAPPED:
		{
		}
		break;
	}
}

UI_Image::~UI_Image()
{
	SDL_DestroyTexture(texture);
}

void UI_Image::update()
{
}

void UI_Image::render()
{
	SDL_Rect output_rect = { (int)std::round(get_pos().x / scale.x),
							 (int)std::round(get_pos().y / scale.y),
							 (int)std::round(get_size().x),
							 (int)std::round(get_size().y) };
	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_RenderCopy(renderer, texture, NULL, &output_rect);
	clear_render_settings(renderer);
}
