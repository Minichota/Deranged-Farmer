#include <vector>

#include "tile.hpp"
#include "renderable.hpp"

class Map : public Renderable
{
	public:
	Map(SDL_Renderer* renderer, const char* data_path, const char* image_path, Ivec tile_size);
	~Map();

	void update();
	void render();

	void init();
	void clear();
	private:
	Ivec tile_size;
	Ivec tile_count;
	const char* data_path;
	const char* image_path;
	std::vector<Tile*> tiles;
};
