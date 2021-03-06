#ifndef ENTITY_CREATOR_HPP
#define ENTITY_CREATOR_HPP

#include <vector>

#include "event-handler.hpp"
#include "level.hpp"
#include "renderable.hpp"
#include "ui-text-input.hpp"
#include "ui-text.hpp"

struct Entity_Creator_Data
{
	std::string name;
	std::vector<std::string> input_repr;
	Fvec size;
	bool rotateable;
};

class Entity_Creator : public Renderable, public Event_Handler
{
	public:
	Entity_Creator(SDL_Renderer* const renderer, Level* level);
	~Entity_Creator();

	void update();
	void render();

	void clear();

	void handle_event(const SDL_Event& event);

	void set_level(Level* level);

	public:
	bool active;

	private:
	Level* level;
	SDL_Rect shadow_rect;
	// for selecting which entity
	std::vector<UI_Text*> entity_names;
	int selected_name;

	// for each field
	std::vector<UI_Text_Input*> inputs;
	int selected_field;

	int curr_state;
	std::vector<Entity_Creator_Data> names;
};

#endif
