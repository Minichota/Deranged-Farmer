#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <functional>

#include "ui-base.hpp"
#include "event-handler.hpp"

class UI_Button : public UI_Base, public Event_Handler
{
	public:
	UI_Button(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::function<void()> callback, SDL_Color color = {});
	~UI_Button();

	void update();
	void render();

	void handle_event(const SDL_Event& event);

	private:
	std::function<void()> callback;
};

#endif
