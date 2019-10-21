#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "game-state.hpp"
#include "ui-base.hpp"

class Level : public Game_State
{
	public:
	Level(SDL_Renderer* renderer, const char* entity_file_path, const char* map_file_path);
	~Level();

	void update();
	void render();

	void init();
	void clear();

	void handle_event(SDL_Event event);

	void push_element(UI_Base* element);
	UI_Base* get_element(size_t index);

	private:
	std::vector<UI_Base*> elements;
	// TODO implement entity class
	//std::vector<Entity*> entities;
	const std::string entity_file_path;
	// TODO implement map
	//Map map;
	const std::string map_file_path;
};

#endif
