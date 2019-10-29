#include <iostream>

#include "map.hpp"
#include "io.hpp"
#include "settings.hpp"

Map::Map(SDL_Renderer* renderer, const char* data_path, const char* image_path):
Renderable(renderer)
{
	this->data_path = data_path;
	this->image_path = image_path;
}

Map::~Map()
{
}

void Map::update()
{
	for(Tile tile : tiles)
	{
		tile.update();
	}
}

void Map::render()
{
	for(Tile tile : tiles)
	{
		tile.render();
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
}

void Map::clear()
{
	for(Tile tile : tiles)
	{
		delete &tile;
	}
	tiles.clear();
}
