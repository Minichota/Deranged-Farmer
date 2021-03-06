#include <cassert>
#include <iostream>

#include "collisions.hpp"
#include "game.hpp"
#include "io.hpp"
#include "map.hpp"
#include "settings.hpp"
#include "util.hpp"

Map::Map(SDL_Renderer* renderer, const char* data_path, const char* image_path,
		 Ivec tile_size) :
Renderable(renderer)
{
	this->player = player;
	this->data_path = data_path;
	this->image_path = image_path;
	this->tile_size = tile_size;
}

Map::~Map()
{
	clear();
}

void Map::update()
{
	for(std::vector<Tile*>& y_tiles : tiles)
	{
		for(Tile* x_tile : y_tiles)
		{
			if(!x_tile->is_null())
			{
				x_tile->update();
			}
		}
	}
	for(Map_Entity* e : map_entities)
	{
		e->update();
	}
	for(Item* item : items)
	{
		item->update();
	}
	camera = player->get_pos();
	if(camera.x - 400 < 0)
	{
		camera.x = 400;
	}
	if(camera.y - 304 < 0)
	{
		camera.y = 304;
	}
	if(camera.x > tile_count.x * tile_size.x - 400)
	{
		camera.x = tile_count.x * tile_size.x - 400;
	}
	if(camera.y > tile_count.y * tile_size.y - 304)
	{
		camera.y = tile_count.y * tile_size.y - 304;
	}
}

void Map::render()
{
	SDL_Rect view_port = { 400 - camera.x, 304 - camera.y,
						   tile_size.x * tile_count.x,
						   tile_size.y * tile_count.y };
	SDL_RenderSetViewport(renderer, &view_port);
	SDL_RenderCopy(renderer, background, NULL, NULL);
	for(std::vector<Tile*>& y_tiles : tiles)
	{
		for(Tile* x_tile : y_tiles)
		{
			if(!(x_tile->get_pos().x + tile_size.x < camera.x - 400 ||
				 x_tile->get_pos().x > camera.x + 400 ||
				 x_tile->get_pos().y + tile_size.y < camera.y - 304 ||
				 x_tile->get_pos().y > camera.y + 304))
			{
				x_tile->render();
			}
		}
	}

	for(Map_Entity* e : map_entities)
	{
		e->render();
	}
	for(Item* item : items)
	{
		item->render();
	}
}

void Map::init()
{
	{
		background = IMG_LoadTexture(renderer, "res/graphics/background.png");
		Error(!background, { "Failed to load background", SDL_GetError() });
	}
	// load file
	std::string data = read(data_path);
	std::vector<Settings::Data<int>*> variables;
	parse(data, '=', variables, 0, 2);
	tile_count = Ivec(variables[0]->data, variables[1]->data);
	for(int i = 0; i < 2; i++)
	{
		delete variables[i];
	}

	std::vector<std::vector<int>> map_data;
	parse_csv(data, map_data, 0, tile_count.y);
	{
		load_tileset(renderer, image_path);
	}
	for(int y = 0; y < tile_count.y; y++)
	{
		for(int x = 0; x < tile_count.x; x++)
		{
			if(map_data[y][x] == 0)
			{
				// null tile
				Tile* tile = new Tile(
					nullptr, Fvec(x * tile_size.x, y * tile_size.y), tile_size);
				if((int)tiles.size() <= y)
				{
					tiles.push_back(std::vector<Tile*>());
				}
				tiles[y].push_back(tile);
				continue;
			}
			int tile_type = map_data[y][x] - 1;
			Tile* tile = new Tile(
				renderer, Fvec(x * tile_size.x, y * tile_size.y), tile_size);
			tile->set_relative_pos(
				Ivec(tile_size.x * (tile_type % tile_size.x),
					 tile_size.y * (int)(tile_type / tile_size.y)));
			if((int)tiles.size() <= y)
			{
				tiles.push_back(std::vector<Tile*>());
			}
			tiles[y].push_back(tile);
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
					Map_Entity* fence = new Map_Entity(
						renderer, 0, Fvec(map_data[y][0], map_data[y][1]),
						Fvec(map_data[y][2], map_data[y][3]), map_data[y][4]);
					fence->load_texture("res/graphics/fence.png");
					map_entities.push_back(fence);
					delete variables[y];
				}
				break;
			}
		}
	}
	variables.clear();
}

void Map::clear()
{
	for(std::vector<Tile*>& y_tiles : tiles)
	{
		for(Tile* x_tile : y_tiles)
		{
			delete x_tile;
		}
		y_tiles.clear();
	}
	for(Map_Entity* map_entity : map_entities)
	{
		delete map_entity;
	}
	map_entities.clear();
	tiles.clear();
}

void Map::handle_collision(Entity* entity)
{
	for(std::vector<Tile*>& y_tiles : tiles)
	{
		for(Tile* x_tile : y_tiles)
		{
			if(!x_tile->is_null())
			{
				if(test_collision(entity->get_collision_pos(),
								  entity->get_collision_size() *
									  entity->get_scale(),
								  x_tile->get_collision_pos(),
								  x_tile->get_collision_size()))
				{
					handle_collision_movingAA(
						entity->get_pos(),
						entity->get_collision_size() * entity->get_scale(),
						entity->get_vel(), x_tile->get_collision_pos(),
						x_tile->get_collision_size());
				}
			}
		}
	}
	for(Map_Entity* map_e : map_entities)
	{
		if(test_collision(entity->get_collision_pos(),
						  entity->get_collision_size() * entity->get_scale(),
						  map_e->get_collision_pos(),
						  map_e->get_collision_size()))
		{
			handle_collision_movingAA(
				entity->get_pos(),
				entity->get_collision_size() * entity->get_scale(),
				entity->get_vel(), map_e->get_collision_pos(),
				map_e->get_collision_size());
		}
	}
}

void Map::validate_pos(Fvec& pos)
{
	pos = Fvec((int)std::round(pos.x) - (int)std::round(pos.x) % tile_size.x,
			   (int)std::round(pos.y) - (int)std::round(pos.y) % tile_size.y);
}

void Map::push_entity(Map_Entity* e)
{
	map_entities.push_back(e);
}

void Map::insert_entity(Map_Entity* e, size_t pos)
{
	map_entities.insert(map_entities.begin() + pos, e);
}

std::vector<std::vector<Tile*>>& Map::get_tiles()
{
	return this->tiles;
}

std::vector<Map_Entity*>& Map::get_map_entities()
{
	return this->map_entities;
}

std::vector<Item*>& Map::get_items()
{
	return this->items;
}

Ivec& Map::get_tile_count()
{
	return tile_count;
}

Tile* Map::get_tile(size_t x, size_t y)
{
	return tiles[y][x];
}

Ivec& Map::get_tile_size()
{
	return tile_size;
}

const char* Map::get_data_path()
{
	return this->data_path;
}

void Map::set_player(Player* player)
{
	this->player = player;
}
