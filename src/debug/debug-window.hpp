#ifndef DEBUG_WINDOW
#define DEBUG_WINDOW

#include <vector>
#include <SDL2/SDL_ttf.h>

#include "renderable.hpp"
#include "vectors.hpp"
#include "event-handler.hpp"

typedef struct
{
	std::string name;
	std::vector<Fvec> values;
} Debug_Element;

class Debug_Window : public Renderable, public Event_Handler
{
	public:
	Debug_Window(SDL_Renderer* renderer);
	~Debug_Window();

	void update();
	void render();

	void handle_event(SDL_Event event);

	void push_render(std::string name_repr, std::vector<Fvec> values);

	void toggle();

	bool active = false;
	private:
	void select(Ivec pos);

	private:
	TTF_Font* font;

	std::vector<Debug_Element> to_render;

	std::vector<SDL_Rect> outer_rects;
	std::vector<SDL_Rect> inner_rects;

	Ivec pos;
	int scroll_pos;

	int outer_selection;
	int inner_selection;
};
#endif
