#ifndef DEBUG_WINDOW_HPP
#define DEBUG_WINDOW_HPP

#include <vector>
#include <SDL2/SDL_ttf.h>

#include "renderable.hpp"
#include "vectors.hpp"
#include "event-handler.hpp"
#include "ui-text.hpp"
#include "ui-text-input.hpp"
#include "sized.hpp"
#include "level.hpp"
#include "entity-creator.hpp"
#include "tile-editor.hpp"
#include "console-log.hpp"

typedef struct
{
	Sized<float>* address;
	std::string name;
	std::vector<float*> values;
	SDL_Texture* texture;
} Debug_Element;

class Debug_Window : public Renderable, public Event_Handler
{
	public:
	Debug_Window(SDL_Renderer* renderer);
	~Debug_Window();

	void update();
	void render();

	void clear();

	void handle_event(const SDL_Event& event);

	void push_render(Sized<float>* address, std::string name_repr, std::vector<float*> values);
	void push_console(std::string text);
	void push_console(float text);
	void push_rect(Fvec pos, Fvec size);
	void push_log(std::vector<const char*> text, long long life_time = 3000);

	void toggle();
	void refresh();

	bool active = false;
	bool rects_active = false;

	void set_level(Level* level);

	private:
	void select(Ivec pos);
	void set_string(std::string input);
	void set_string(float input);
	void handle_keyboard_scrolling();
	void reload_inputs();

	private:
	Level* level;

	TTF_Font* font;

	std::vector<Debug_Element> to_render;
	std::vector<SDL_Rect> rects;

	std::vector<SDL_Rect> outer_rects;
	std::vector<SDL_Rect> inner_rects;

	Entity_Creator entity_creator;

	std::vector<Console_Log> logs;

	Ivec pos;
	int scroll_pos;

	int outer_selection;
	int inner_selection;

	std::vector<UI_Text_Input*> text_inputs;

	UI_Text console;
};
void remove_zeros(std::string& input);
#endif
