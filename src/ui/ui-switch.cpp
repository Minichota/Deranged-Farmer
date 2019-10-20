#include "ui-switch.hpp"

UI_Switch::UI_Switch(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color color):
UI_Base(renderer, pos, size, scale, color)
{
	this->toggle = false;
}

UI_Switch::~UI_Switch()
{
}

void UI_Switch::update()
{
}

void UI_Switch::render()
{
	SDL_Rect border = {get_pos().x, get_pos().y, (int)(size.x * scale.x), (int)(size.y * scale.y)};
	SDL_Rect fill;
	if(toggle)
	{
		fill = {get_pos().x + (int)(2 * scale.x),
				get_pos().y + (int)(2 * scale.y),
				(int)((size.x * scale.x) - (4 * scale.x)),
				(int)((size.y * scale.y) - (4 * scale.y))};
	}
	else
	{
		fill = {0,0,0,0};
	}

	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &border);
	SDL_RenderFillRect(renderer, &fill);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
}

void UI_Switch::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			if(in_bounds(Ivec(event.button.x, event.button.y)))
			{
				toggle = !toggle;
			}
		} break;
	}
}

bool UI_Switch::is_on()
{
	return toggle;
}
