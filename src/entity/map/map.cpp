#include <iostream>
#include <cassert>

#include "map.hpp"
#include "io.hpp"
#include "settings.hpp"
#include "collisions.hpp"

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
	for(Map_Entity* e : map_entities)
	{
		e->update();
	}
}

void Map::render()
{
	for(Tile* tile : tiles)
	{
		tile->render();
	}
	for(Map_Entity* e : map_entities)
	{
		e->render();
	}
}

void Map::init()
{
	// load file
	std::string data = read(data_path);
	std::vector<Settings::Data<int>*> variables;
	parse(data, '=', variables, 0, 2);
	tile_count = Ivec(variables[0]->data, variables[1]->data);

	std::vector<std::vector<int>> map_data;
	parse_csv(data, map_data, 0, tile_count.y);

	SDL_Texture* image_texture = IMG_LoadTexture(renderer, image_path);
	for(int y = 0; y < tile_count.y; y++)
	{
		for(int x = 0; x < tile_count.x; x++)
		{
			if(map_data[y][x] == 0)
			{
				// null tile
				Tile* tile = new Tile();
				tiles.push_back(tile);
				continue;
			}
			int tile_type = map_data[y][x] - 1;
			Tile* tile = new Tile(renderer, Ivec(x * tile_size.x, y * tile_size.y), tile_size);
			tile->set_texture(image_texture, Ivec(tile_size.x * (tile_type % tile_size.x), tile_size.y * (int)(tile_type / tile_size.y)));
			tiles.push_back(tile);
		}
	}

	variables.clear();
	map_data.clear();
	parse(data, '=', variables, 2);
	parse_csv(data, map_data, tile_count.y);
	assert(variables.size() == map_data.size());
	for(size_t y = 0; y < variables.size(); y++)
	{
		if(variables[y]->name == "type")
		{
			switch(variables[y]->data)
			{
				case 0:
				{
					Map_Entity* fence = new Map_Entity(renderer, Fvec(map_data[y][0], map_data[y][1]), Fvec(map_data[y][2], map_data[y][3]), map_data[y][4]);
					fence->load_texture("res/graphics/fence.png");
					map_entities.push_back(fence);
				}
			}
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

void Map::handle_collision(Entity* entity)
{
	for(Tile* tile : tiles)
	{
		if(test_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
								   tile->get_pos(), tile->get_size()))
		{
			handle_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
									  tile->get_pos(), tile->get_size());
		}
	}
	for(Map_Entity* map_e : map_entities)
	{
		if(test_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
								   map_e->get_pos(), map_e->get_size()))
		{
			handle_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
									  map_e->get_pos(), map_e->get_size());
		}
	}
}

Tile* Map::get_tile(size_t x, size_t y)
{
	return tiles[y * tile_count.x + x];
}

Ivec& Map::get_tile_size()
{
	return tile_size;
}
