#include <SDL2/SDL.h>

#include "ai-roaming.hpp"
#include "game.hpp"

AI_Roaming::AI_Roaming(Map& map, Entity* parent, long long delay):
AI(map, parent)
{
	this->delay = delay;
	this->last_time = -10000;
}

void AI_Roaming::update()
{
	this->goal_position = normalize(Fvec(300,100), map.get_tile_size());
	Game::debug->push_console(goal_position.x);
	Game::debug->push_console(goal_position.y);
	long long curr_time = SDL_GetTicks();
	if(curr_time - last_time > delay)
	{
		std::cout << "generated path" << std::endl;
		last_time = curr_time;
		generate_path();

		while(&pos != nullptr){
			std::cout << pos.pos << std::endl;
			if(pos.parent == nullptr)
			{
				break;
			}
			pos = *pos.parent;
		}
	}
}

void AI_Roaming::generate_path()
{
	std::vector<std::vector<Tile*>>& tiles = map.get_tiles();
	std::vector<Map_Entity*>& map_entities = map.get_map_entities();

	// generation of all tile positions and whether or not they're passable
	std::vector<std::vector<struct Position>> tile_positions;

	Ivec parent_index;
	for(size_t y = 0; y < tiles.size(); y++)
	{
		tile_positions.push_back(std::vector<Position>());
		for(size_t x = 0; x < tiles[y].size(); x++)
		{
			if(tiles[y][x]->get_pos() == normalize(parent->get_collision_pos(), map.get_tile_size()))
			{
				parent_index = Ivec(x, y);
			}
			bool flag = true;
			if(tiles[y][x]->is_null())
			{
				for(Map_Entity* map_entity : map_entities)
				{
					Fvec top_left  = normalize(map_entity->get_collision_pos(), map.get_tile_size());
					Fvec bot_right = normalize(map_entity->get_collision_pos() + map_entity->get_collision_size(), map.get_tile_size());
					if((top_left == tiles[y][x]->get_pos() || bot_right == tiles[y][x]->get_pos()))
					{
						flag = false;
						break;
					}
				}
				tile_positions[y].push_back(Position{Ivec(x, y), tiles[y][x]->get_pos(), flag});
			}
			else
			{
				tile_positions[y].push_back(Position{Ivec(x, y), tiles[y][x]->get_pos(), false});
			}
		}
	}
	// pathfinding
	std::queue<Position> q;
	q.push(Position{parent_index, normalize(this->parent->get_collision_pos(), map.get_tile_size()), true, false});
	while(!q.empty())
	{
		Position* v = new Position(q.front());
		q.pop();
		if(v->pos == goal_position)
		{
			Position* x = v;
			std::cout << "found the end" << v->pos << std::endl;
			pos = *x;
			return;
		}
		std::vector<Position*> adjacents;
		if(v->index.x > 0)
		{
			if(tile_positions[v->index.y][v->index.x - 1].null)
			{
				adjacents.push_back(&tile_positions[v->index.y][v->index.x - 1]);
			}
		}
		if(v->index.x + 1 < (int)tile_positions[parent_index.y].size())
		{
			if(tile_positions[v->index.y][v->index.x + 1].null)
			{
				adjacents.push_back(&tile_positions[v->index.y][v->index.x + 1]);
			}
		}
		if(v->index.y > 0)
		{
			if(tile_positions[v->index.y - 1][v->index.x].null)
			{
				adjacents.push_back(&tile_positions[v->index.y - 1][v->index.x]);
			}
		}
		if(v->index.x + 1 < (int)tile_positions.size())
		{
			if(tile_positions[v->index.y + 1][v->index.x].null)
			{
				adjacents.push_back(&tile_positions[v->index.y + 1][v->index.x]);
			}
		}
		for(Position* p : adjacents)
		{
			if(p->index.x <= (int)tiles[0].size() && p->index.y <= (int)tiles.size())
			{
				if(!p->checked)
				{
					p->checked = true;
					p->parent = v;
					q.push(*p);
				}
			}
		}
	}
	std::cout << "did not find the end" << std::endl;
}
