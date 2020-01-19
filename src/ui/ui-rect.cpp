#include "ui-rect.hpp"
#include "util.hpp"

UI_Rect::UI_Rect(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale,
				 SDL_Color color, Fill_Type type) :
UI_Base(renderer, pos, size, scale, color)
{
	this->type = type;
}

UI_Rect::~UI_Rect()
{
}

void UI_Rect::update()
{
}

void UI_Rect::render()
{
	this->sprite = { (int)std::round(pos.x - origin.x + camera.x - 400),
					 (int)std::round(pos.y - origin.y + camera.y - 304),
					 (int)std::round(this->size.x * scale.x),
					 (int)std::round(this->size.y * scale.y) };
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	// SDL_RenderSetScale(renderer, this->scale.x, this->scale.y);
	switch(type)
	{
		case FILL:
		{
			SDL_RenderFillRect(renderer, &sprite);
		}
		break;
		case NORMAL:
		{
			SDL_RenderDrawRect(renderer, &sprite);
		}
		break;
		case WRAPPED:
		{
		}
		break;
	}
	clear_render_settings(renderer);
}
