#include <iostream>

#include "map.hpp"
#include "io.hpp"
#include "settings.hpp"

Map::Map(SDL_Renderer* renderer, const char* data_path, const char* image_path, Ivec tile_size):
Renderable(renderer)
{
	this->data_path = data_path;
	this->image_path = image_path;
	this->tile_size = tile_size;
}

Map::~Map()
{
}

void Map::update()
{
	for(Tile* tile : tiles)
	{
		tile->update();
	}
}

void Map::render()
{
	for(Tile* tile : tiles)
	{
		tile->render();
	}
}

void Map::init()
{
	// load file
	std::string data = read(data_path);
	std::vector<Settings::Data<int>*> tile_count;
	parse(data, '=', tile_count);

	std::vector<std::vector<int>> map_data;
	parse_csv(data, map_data);

	for(size_t y = 0; y < map_data.size(); y++)
	{
		for(size_t x = 0; x < map_data[y].size(); x++)
		{
			if(map_data[y][x] == 0)
			{
				// null tile
				continue;
			}
			int tile_type = map_data[y][x] - 1;
			Tile* tile = new Tile(renderer, Ivec(x * tile_size.x, y * tile_size.y), tile_size);
			SDL_Texture* image_texture = IMG_LoadTexture(renderer, image_path);
			tile->set_texture(image_texture, Ivec(tile_size.x * (tile_type % tile_size.x), tile_size.y * (int)(tile_type / tile_size.y)));
			tiles.push_back(tile);
		}
	}
}

void Map::clear()
{
	for(Tile* tile : tiles)
	{
		delete tile;
	}
	tiles.clear();
}
