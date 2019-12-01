#include <SDL2/SDL.h>

#include "ai-roaming.hpp"

AI_Roaming::AI_Roaming(Map& map, Entity* parent, long long delay):
AI(map, parent)
{
	this->delay = delay;
}

void AI_Roaming::update()
{
	long long curr_time = SDL_GetTicks();
	if(curr_time - last_time > delay)
	{
		last_time = curr_time;
		generate_path();
	}
}

void AI_Roaming::generate_path()
{
	std::vector<std::vector<Tile*>> tiles = map.get_tiles();
	std::vector<Map_Entity*> map_entities = map.get_map_entities();

	// generation of all tile positions and whether or not they're passable
	std::vector<std::vector<struct Position>> tile_positions;
	for(size_t y = 0; y < tiles.size(); y++)
	{
		tile_positions.push_back(std::vector<Position>());
		for(size_t x = 0; x < tiles[y].size(); x++)
		{
			for(Map_Entity* map_entity : map_entities)
			{
				Fvec top_left  = normalize(map_entity->get_pos(), map.get_tile_size());
				Fvec bot_right = normalize(map_entity->get_collision_pos() + map_entity->get_collision_size(), map.get_tile_size());
				if((top_left == tiles[y][x]->get_pos() || bot_right == tiles[y][x]->get_pos()) && tiles[y][x]->is_null())
				{
					tile_positions[y].push_back(Position{tiles[y][x]->get_pos(), true});
				}
				else
				{
					tile_positions[y].push_back(Position{tiles[y][x]->get_pos(), false});
				}
			}
		}
	}
}
