#include <iostream>

#include "debug-window.hpp"
#include "debug.hpp"

#define MAX_SCROLL 600

Debug_Window::Debug_Window(SDL_Renderer* renderer):
Renderable(renderer)
{
	this->pos = Ivec(600,0);
	scroll_pos = 0;
}

Debug_Window::~Debug_Window()
{
}

void Debug_Window::update()
{
}

void Debug_Window::render()
{
	if(Debug::active)
	{
		Ivec draw_pos = {this->pos.x, this->pos.y - scroll_pos};
		Debug::render_debug_text(renderer, draw_pos);
	}
}

void Debug_Window::handle_event(SDL_Event event)
{
	if(Debug::active)
	{
		switch(event.type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				Ivec mouse_position = Ivec(event.button.x, event.button.y);
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
					{
						Debug::open_selection(mouse_position);
					} break;
				}
			} break;
			case SDL_MOUSEWHEEL:
			{
				if(event.wheel.y > 0)
				{
					// scroll up
					this->scroll_pos -= 10;
					if(scroll_pos < 0)
					{
						scroll_pos = 0;
					}
				}
				if(event.wheel.y < 0)
				{
					// scroll down
					this->scroll_pos += 10;
					if(scroll_pos > MAX_SCROLL)
					{
						scroll_pos = MAX_SCROLL;
					}
				}
			} break;
		}
	}
}
