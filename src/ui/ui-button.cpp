#include <iostream>

#include "ui-button.hpp"

UI_Button::UI_Button(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::function<void()> callback):
UI_Base(renderer, pos, size, scale),
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
	SDL_Rect box = {(int)(this->pos.x/this->scale.x),
					(int)(this->pos.y/this->scale.y),
					this->size.x,
					this->size.y};
	SDL_RenderSetScale(renderer, this->scale.x, this->scale.y);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &box);
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
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

bool UI_Button::in_bounds(Ivec input_pos)
{
	Ivec actual_size = this->size * this->scale;
	Ivec bottom_left = Ivec(this->pos.x + actual_size.x,
							this->pos.y + actual_size.y);
	return this->pos.x <= input_pos.x &&
			input_pos.x <= bottom_left.x &&
			this->pos.y <= input_pos.y &&
			input_pos.y <= bottom_left.y;
}
