#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "game-state.hpp"
#include "ui-base.hpp"
#include "entity.hpp"
#include "map.hpp"

class Level : public Game_State
{
	public:
	Level(SDL_Renderer* renderer, const char* entity_file_path, const char* map_data_file_path, const char* map_image_file_path);
	~Level();

	void update();
	void render();

	void init();
	void clear();

	void handle_event(const SDL_Event& event);

	Map& get_map();
	void push_entity(Entity* entity);

	private:
	void load_entities();
	void handle_entity_collision(Entity* e_1, Entity* e_2);

	private:
	SDL_Texture* background;
	std::vector<Entity*> entities;
	const std::string entity_file_path;
	Map map;
	const std::string map_data_file_path;
	const std::string map_image_file_path;
};

#endif
