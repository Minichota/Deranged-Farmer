#include <vector>

#include "tile.hpp"
#include "renderable.hpp"

class Map : public Renderable
{
	public:
	Map(SDL_Renderer* renderer, const char* data_path, const char* image_path);
	~Map();

	void update();
	void render();

	void init();
	void clear();
	private:
	const char* data_path;
	const char* image_path;
	std::vector<Tile> tiles;
};
