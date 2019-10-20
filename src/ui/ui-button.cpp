#include <iostream>

#include "ui-button.hpp"

UI_Button::UI_Button(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::function<void()> callback, SDL_Color color):
UI_Base(renderer, pos, size, scale, color),
callback(callback)
{
}

UI_Button::~UI_Button()
{
}

void UI_Button::update()
{
}

void UI_Button::render()
{
	SDL_Rect box = {get_pos().x,
					get_pos().y,
					this->size.x,
					this->size.y};
	SDL_RenderSetScale(renderer, this->scale.x, this->scale.y);
	SDL_SetRenderDrawColor(renderer, color.r, color.b, color.b, color.a);
	SDL_RenderDrawRect(renderer, &box);
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void UI_Button::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			switch(event.button.button)
			{
					case SDL_BUTTON_LEFT:
					{
						if(in_bounds(Ivec(event.button.x, event.button.y)))
						{
							callback();
						}
					} break;
			}
		} break;
	}
}
