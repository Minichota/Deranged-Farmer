#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "tile.hpp"
#include "renderable.hpp"
#include "entity.hpp"
#include "map-entity.hpp"

class Map : public Renderable
{
	public:
	Map(SDL_Renderer* renderer, const char* data_path, const char* image_path, Ivec tile_size);
	~Map();

	void update();
	void render();

	void init();
	void clear();

	void handle_collision(Entity* entity);

	void validate_pos(Fvec& pos);

	void push_tile(Tile* tile);
	void insert_tile(Tile* tile, STvec pos);

	void push_entity(Map_Entity* tile);
	void insert_entity(Map_Entity* tile, size_t pos);

	std::vector<std::vector<Tile*>> get_tiles();
	Ivec& get_tile_count();
	Tile* get_tile(size_t x, size_t y);
	Ivec& get_tile_size();

	private:
	Ivec tile_size;
	Ivec tile_count;
	const char* data_path;
	const char* image_path;
	std::vector<std::vector<Tile*>> tiles;
	std::vector<Map_Entity*> map_entities;
	SDL_Texture* tile_image;
};
#endif
