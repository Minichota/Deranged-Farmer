#include <iostream>

#include "ui-text-input.hpp"

UI_Text_Input::UI_Text_Input(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::string font_path, SDL_Color font_color):
UI_Base(renderer, pos, size, scale),
ui_text(renderer, pos, size, scale, "", font_path, font_color)
{
	SDL_StartTextInput();
}

UI_Text_Input::~UI_Text_Input()
{
	this->text.clear();
}

void UI_Text_Input::update()
{
	this->ui_text.set_text(this->text);
	this->ui_text.update();
}

void UI_Text_Input::render()
{
	ui_text.render();
}

void UI_Text_Input::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_TEXTINPUT:
		{
			this->text.append(event.text.text);
		} break;
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_BACKSPACE:
				{
					if(this->text.size() > 0)
					{
						this->text.pop_back();
					}
				} break;
			}
		} break;
	}
}
