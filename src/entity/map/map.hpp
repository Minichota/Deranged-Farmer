#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "entity.hpp"
#include "item.hpp"
#include "map-entity.hpp"
#include "player.hpp"
#include "renderable.hpp"
#include "tile.hpp"

class Map : public Renderable
{
	public:
	Map(SDL_Renderer* renderer, const char* data_path, const char* image_path,
		Ivec tile_size);
	~Map();

	void update();
	void render();

	void init();
	void clear();

	void handle_collision(Entity* entity);

	void validate_pos(Fvec& pos);

	void push_entity(Map_Entity* tile);
	void insert_entity(Map_Entity* tile, size_t pos);

	std::vector<std::vector<Tile*>>& get_tiles();
	std::vector<Item*>& get_items();
	std::vector<Map_Entity*>& get_map_entities();
	Ivec& get_tile_count();
	Tile* get_tile(size_t x, size_t y);
	Ivec& get_tile_size();

	void set_player(Player* player);

	const char* get_data_path();

	private:
	Ivec tile_size;
	Ivec tile_count;
	const char* data_path;
	const char* image_path;
	std::vector<std::vector<Tile*>> tiles;
	std::vector<Item*> items;
	std::vector<Map_Entity*> map_entities;
	Player* player;
};
#endif
