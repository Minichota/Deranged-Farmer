#ifndef DEBUG_WINDOW
#define DEBUG_WINDOW

#include "renderable.hpp"
#include "vectors.hpp"
#include "event-handler.hpp"

class Debug_Window : public Renderable, public Event_Handler
{
	public:
	Debug_Window(SDL_Renderer* renderer);
	~Debug_Window();

	void update();
	void render();

	void handle_event(SDL_Event event);

	private:
	Ivec pos;
	int scroll_pos;

	bool active;
};
#endif
