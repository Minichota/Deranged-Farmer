#include <iostream>

#include "ui-text-input.hpp"

UI_Text_Input::UI_Text_Input(SDL_Renderer* renderer, Ivec pos, Ivec size,
							 Fvec scale, std::string font_path,
							 SDL_Color font_color, Fill_Type type) :
UI_Base(renderer, pos, size, scale, font_color),
ui_text(renderer, pos, size, scale, "", font_path, font_color, type)
{
	SDL_StartTextInput();
}

UI_Text_Input::~UI_Text_Input()
{
	this->text.clear();
}

void UI_Text_Input::update()
{
	this->ui_text.set_scale(scale);
	this->ui_text.set_abs_pos(pos);
	this->ui_text.set_origin(origin);
	this->ui_text.set_text(this->text);
	this->ui_text.update();
}

void UI_Text_Input::render()
{
	if(ui_text.get_text().size() > 0)
	{
		ui_text.render();
	}
}

void UI_Text_Input::handle_event(const SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_TEXTINPUT:
		{
			this->text.append(event.text.text);
		}
		break;
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
				}
				break;
			}
		}
		break;
	}
}

UI_Text& UI_Text_Input::get_text()
{
	return this->ui_text;
}

void UI_Text_Input::set_string(std::string str)
{
	this->text = str;
	this->ui_text.set_text(this->text);
}

std::string& UI_Text_Input::get_string()
{
	return this->text;
}

Ivec& UI_Text_Input::get_size()
{
	return this->ui_text.get_size();
}

void UI_Text_Input::set_font_size(size_t size)
{
	this->ui_text.set_font_size(size);
}
