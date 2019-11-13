#include <iostream>
#include <cassert>

#include "game.hpp"
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
		if(tile->get_size() != Fvec(-1, -1))
		{
			tile->update();
		}
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
		if(tile->get_size() != Fvec(-1, -1))
		{
		  tile->render();
		}
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
				Tile* tile = new Tile(nullptr, Fvec(x * tile_size.x, y * tile_size.y), Fvec(-1,-1));
				tiles.push_back(tile);
				continue;
			}
			int tile_type = map_data[y][x] - 1;
			Tile* tile = new Tile(renderer, Fvec(x * tile_size.x, y * tile_size.y), tile_size);
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
		if(tile->get_size() != Fvec(-1, -1))
		{
			if(test_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
									   tile->get_pos_copy(), tile->get_size_copy()))
			{
				handle_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
										  tile->get_pos_copy(), tile->get_size_copy());
			}
		}
	}
	for(Map_Entity* map_e : map_entities)
	{
		if(test_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
								   map_e->get_pos_copy(), map_e->get_size_copy()))
		{
			handle_collision_movingAA(entity->get_pos(), entity->get_size() * entity->get_scale(), entity->get_vel(),
									  map_e->get_pos_copy(), map_e->get_size_copy());
		}
	}
}

void Map::validate_pos(Fvec& pos)
{
	// TODO implement validate_pos
}

std::vector<Fvec> Map::get_empty_tiles()
{
	std::vector<Fvec> tile_pos;
	for(Tile* tile : tiles)
	{
		// filling
		if(tile->get_size() == Fvec(-1, -1))
		{
			tile_pos.push_back(tile->get_pos());
		}
	}
	for(size_t i = 0; i < map_entities.size(); i++)
	{
		// removing garbage values
		Fvec top_left = map_entities[i]->get_pos();
		Fvec top_right = Fvec(map_entities[i]->get_pos().x + map_entities[i]->get_size().x,
							  map_entities[i]->get_pos().y);
		Fvec bot_left = Fvec(map_entities[i]->get_pos().x,
							  map_entities[i]->get_pos().y + map_entities[i]->get_size().y);
		Fvec bot_right = Fvec(map_entities[i]->get_pos().x + map_entities[i]->get_size().x,
							  map_entities[i]->get_pos().y + map_entities[i]->get_size().y);

		const auto normalize = [](const Fvec& x, const Ivec tile_size)
		{
			// basically floors the value
			return Fvec(x.x - (int)(x.x)%tile_size.x, x.y - (int)(x.y)%tile_size.y);
		};
		top_left = normalize(top_left, tile_size);
		top_right = normalize(top_right, tile_size);
		bot_left = normalize(bot_left, tile_size);
		bot_right = normalize(bot_right, tile_size);
		for(size_t j = 0; j < tile_pos.size(); j++)
		{
			if(tile_pos[j] == top_left ||
			   tile_pos[j] == top_right ||
			   tile_pos[j] == bot_left ||
			   tile_pos[j] == bot_right)
			{
				tile_pos.erase(tile_pos.begin() + j);
			}
		}
	}
	return tile_pos;
}

Tile* Map::get_tile(size_t x, size_t y)
{
	return tiles[y * tile_count.x + x];
}

Ivec& Map::get_tile_size()
{
	return tile_size;
}
