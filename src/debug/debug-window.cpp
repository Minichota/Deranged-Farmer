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
	Ivec pos = {this->pos.x, this->pos.y - scroll_pos};
	if(Debug::active)
	{
		Debug::render_debug_text(renderer, pos);
	}
}

void Debug_Window::handle_event(SDL_Event event)
{
	if(Debug::active)
	{
		switch(event.type)
		{
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
