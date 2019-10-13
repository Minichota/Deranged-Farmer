#ifndef UI_TEXT_INPUT_HPP
#define UI_TEXT_INPUT_HPP

#include "ui-base.hpp"
#include "ui-text.hpp"
#include "event-handler.hpp"

class UI_Text_Input : public UI_Base, public Event_Handler
{
	public:
	UI_Text_Input(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::string font_path, SDL_Color font_color);
	~UI_Text_Input();

	void update();
	void render();

	void handle_event(SDL_Event event);

	private:
	UI_Text ui_text;
	std::string text;
};

#endif
