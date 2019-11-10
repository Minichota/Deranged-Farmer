#include "ui-rect.hpp"
#include "util.hpp"

UI_Rect::UI_Rect(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color color, Fill_Type type):
UI_Base(renderer, pos, size, scale, color)
{
	this->type = type;
}

UI_Rect::~UI_Rect()
{
}

void UI_Rect::update()
{
	this->sprite =
	{
		get_pos().x,
		get_pos().y,
		this->size.x,
		this->size.y
	};
}

void UI_Rect::render()
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderSetScale(renderer, this->scale.x, this->scale.y);
	switch(type)
	{
		case FILL:
		{
			SDL_RenderFillRect(renderer, &sprite);
		} break;
		case NORMAL:
		{
			SDL_RenderDrawRect(renderer, &sprite);
		} break;
	}
	clear_render_settings(renderer);
}
