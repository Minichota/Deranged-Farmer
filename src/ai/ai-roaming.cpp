#include <SDL2/SDL.h>

#include "ai-roaming.hpp"
#include "game.hpp"

AI_Roaming::AI_Roaming(Map& map, Entity* parent, long long delay) :
AI(map, parent)
{
	this->delay = delay;
	this->last_time = -10000;
}

void AI_Roaming::update()
{
	long long curr_time = SDL_GetTicks();
	if(curr_time - last_time > delay && done)
	{
		// this->goal_position = normalize(Fvec(rand()%800,rand()%608),
		// map.get_tile_size());
		float r = 300 * sqrt((rand() % 300) / 300.0f);
		float theta = rand() * 2 * 3.1415926f;
		this->goal_position.x = parent->get_collision_pos().x +
								parent->get_collision_size().x / 2 +
								r * cosf(theta);
		this->goal_position.y = parent->get_collision_pos().y +
								parent->get_size().y / 2 + r * sinf(theta);
		this->goal_position = normalize(goal_position, map.get_tile_size());
		done = false;
		if((done = !generate_path()))
		{
			last_time = curr_time;
		}
		prev_location = curr_time;
	}

	if(pos->pos != Fvec(-1.0f, -1.0f) && !done)
	{
		Fvec delta_pos = pos->pos - parent->get_collision_pos();
		if(abs(delta_pos.x) > 5)
		{
			parent->accelerate(Fvec(delta_pos.x, 0.0f));
		}
		else if(abs(delta_pos.y) > 5)
		{
			parent->accelerate(Fvec(0.0f, delta_pos.y));
		}
		if(abs((delta_pos.x) <= 5 && abs(delta_pos.y) <= 5))
		{
			if(pos->parent != nullptr)
			{
				Position* previous = pos;
				pos = pos->parent;
				prev_location = curr_time;
				delete previous;
			}
			else
			{
				done = true;
				last_time = curr_time;
				delete pos;
			}
		}
	}

	if(curr_time - prev_location > threshold)
	{
		done = true;
	}
}

bool AI_Roaming::generate_path()
{
	std::vector<std::vector<Tile*>>& tiles = map.get_tiles();
	std::vector<Map_Entity*>& map_entities = map.get_map_entities();

	// generation of all tile positions and whether or not they're passable
	std::vector<std::vector<Position>> tile_positions;

	Ivec parent_index;
	for(size_t y = 0; y < tiles.size(); y++)
	{
		tile_positions.emplace_back();
		for(size_t x = 0; x < tiles[y].size(); x++)
		{
			if(tiles[y][x]->get_pos() ==
			   normalize(parent->get_collision_pos(), map.get_tile_size()))
			{
				parent_index = Ivec(x, y);
			}
			bool flag = true;
			if(tiles[y][x]->is_null())
			{
				for(Map_Entity* map_entity : map_entities)
				{
					Fvec top_left = normalize(map_entity->get_collision_pos(),
											  map.get_tile_size());
					Fvec bot_right =
						normalize(map_entity->get_collision_pos() +
									  map_entity->get_collision_size(),
								  map.get_tile_size());
					if(top_left == tiles[y][x]->get_pos() ||
					   bot_right == tiles[y][x]->get_pos())
					{
						flag = false;
						break;
					}
				}
				tile_positions[y].push_back(
					Position{ Ivec(x, y), tiles[y][x]->get_pos(), flag });
			}
			else
			{
				tile_positions[y].push_back(
					Position{ Ivec(x, y), tiles[y][x]->get_pos(), false });
			}
		}
	}

	// pathfinding
	std::queue<Position> q;
	std::vector<Position*> cleanups;
	q.push(Position{
		parent_index,
		normalize(this->parent->get_collision_pos(), map.get_tile_size()), true,
		false });
	while(!q.empty())
	{
		Position* v = new Position(q.front());
		cleanups.push_back(v);
		q.pop();
		if(v->pos == goal_position)
		{
			Position* x = v;
			// reversing linked list
			/*
			   (1->2->3) ->
			   -> (3->2->1)
			*/
			Position* current = x;
			Position* next = nullptr;
			Position* prev = nullptr;
			while(current->parent != nullptr)
			{
				next = current->parent;
				current->parent = prev;
				prev = current;
				current = next;
			}
			if(prev != nullptr)
			{
				pos = prev;
			}
			else
			{
				// entity is already at position
				// cleaning positions
				for(size_t i = 0; i < cleanups.size(); i++)
				{
					delete cleanups[i];
				}
				pos = new Position();
			}
			return true;
		}
		std::vector<Position*> adjacents;
		adjacents.reserve(4);
		if(v->index.x > 0)
		{
			if(tile_positions[v->index.y][v->index.x - 1].null)
			{
				// left tile is null and will be checked
				adjacents.push_back(
					&tile_positions[v->index.y][v->index.x - 1]);
			}
		}
		if(v->index.x + 1 < (int)tile_positions[parent_index.y].size())
		{
			if(tile_positions[v->index.y][v->index.x + 1].null)
			{
				// right tile is null and will be checked
				adjacents.push_back(
					&tile_positions[v->index.y][v->index.x + 1]);
			}
		}
		if(v->index.y > 0)
		{
			if(tile_positions[v->index.y - 1][v->index.x].null)
			{
				// top tile is null and will be checked
				adjacents.push_back(
					&tile_positions[v->index.y - 1][v->index.x]);
			}
		}
		if(v->index.y + 1 < (int)tile_positions.size())
		{
			if(tile_positions[v->index.y + 1][v->index.x].null)
			{
				// bottom tile is null and will be checked
				adjacents.push_back(
					&tile_positions[v->index.y + 1][v->index.x]);
			}
		}
		for(Position* p : adjacents)
		{
			if(p->index.x <= (int)tiles[0].size() &&
			   p->index.y <= (int)tiles.size())
			{
				if(!p->checked)
				{
					// tile has not been checked yet
					p->checked = true;
					p->parent = v;
					q.push(*p);
				}
			}
		}
	}
	// cleaning positions
	for(size_t i = 0; i < cleanups.size(); i++)
	{
		delete cleanups[i];
	}
	pos = new Position();
	return false;
}
