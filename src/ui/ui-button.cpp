#include <iostream>

#include "ui-button.hpp"
#include "util.hpp"

UI_Button::UI_Button(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale,
					 std::function<void()> callback, SDL_Color color) :
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
	SDL_Rect box = {
		(int)std::round(pos.x - origin.x * scale.x + camera.x - 400),
		(int)std::round(pos.y - origin.y * scale.y + camera.y - 304),
		(int)std::round(size.x * scale.x),
		(int)std::round(size.y * (int)scale.y)
	};
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &box);
	clear_render_settings(renderer);
}

void UI_Button::handle_event(const SDL_Event& event)
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
				}
				break;
			}
		}
		break;
	}
}
