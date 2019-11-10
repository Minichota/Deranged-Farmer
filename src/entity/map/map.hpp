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

	Tile* get_tile(size_t x, size_t y);
	Ivec& get_tile_size();

	private:
	Ivec tile_size;
	Ivec tile_count;
	const char* data_path;
	const char* image_path;
	std::vector<Tile*> tiles;
	std::vector<Map_Entity*> map_entities;
};
