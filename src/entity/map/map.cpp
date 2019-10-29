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
	std::vector<Settings::Data<int>*> size =
	{
		new Settings::Data<int>{"width"},
		new Settings::Data<int>{"height"}
	};
	parse(data, '=', size);
	std::vector<std::vector<int>> map_data;
	parse_csv(data, map_data);
}

void Map::clear()
{
	for(Tile* tile : tiles)
	{
		delete tile;
	}
	tiles.clear();
}
