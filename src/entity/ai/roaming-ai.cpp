#include <queue>
#include <algorithm>

#include "game.hpp"
#include "roaming-ai.hpp"
#include "tile.hpp"

Roaming_AI::Roaming_AI(Entity* parent, Map* map, const float radius, const long delay_of_movements):
AI(parent, map),
radius(radius),
delay_of_movements(delay_of_movements)
{
	prev_time = -10000000;
	completed_movement = true;
}

Roaming_AI::~Roaming_AI()
{
}

void Roaming_AI::update()
{
	if(SDL_GetTicks() - prev_time >= delay_of_movements && completed_movement)
	{
		prev_time = SDL_GetTicks();
		float r = radius * sqrt((rand() % 1000) / 1000.0f);
		float theta = rand() * 2 * 3.1415926f;

		end_pos.x = parent->get_pos().x + parent->get_size().x / 2 + r * cosf(theta);
		end_pos.y = parent->get_pos().y + parent->get_size().y / 2 + r * sinf(theta);

		map->validate_pos(end_pos);

		std::cout << "final position: " << end_pos << std::endl;
		calculate_path();
		if(nodes.size() > 0)
		{
			Candidate x = nodes.top();
			while(x.parent != nullptr)
			{
				std::cout << x.tile->get_pos() << std::endl;
				x = *x.parent;
			}
		}
	}
	if(Game::debug->active)
	{
		Game::debug->push_console(end_pos.x);
		Game::debug->push_console(end_pos.y);
	}
	// TODO implement moving to positions
}

void Roaming_AI::calculate_path()
{
	while(!nodes.empty())
	{
		nodes.pop();
	}
	std::vector<std::vector<Tile*>> candidates = map->get_tiles();
	Fvec curr_pos = this->parent->get_pos();
	map->validate_pos(curr_pos);
	Tile* tile = nullptr;
	size_t x_pos = -1;
	size_t y_pos = -1;
	for(size_t i = 0; i < candidates.size(); i++)
	{
		if(std::find_if(candidates[i].begin(), candidates[i].end(), [&curr_pos](Tile*& tile) { return tile->get_pos() == curr_pos;}) != candidates[i].end())
		{
			tile = *std::find_if(candidates[i].begin(), candidates[i].end(), [&curr_pos](Tile*& tile) { return tile->get_pos() == curr_pos;});
			x_pos = std::find_if(candidates[i].begin(), candidates[i].end(), [&curr_pos](Tile*& tile) { return tile->get_pos() == curr_pos;}) - candidates[i].begin();
			y_pos = i;
		}
	}
	if(tile == nullptr)
	{
		return;
	}
	else if(tile->get_size() != Fvec(-1, -1))
	{
		return;
	}

	std::vector<std::vector<Candidate>> final_cands;
	for(size_t y = 0; y < candidates.size(); y++)
	{
		final_cands.push_back(std::vector<Candidate>());
		for(size_t x = 0; x < candidates.size(); x++)
		{
			final_cands[y].push_back(Candidate{candidates[y][x], x, y, false});
		}
	}

	std::queue<Candidate> q;
	q.push(Candidate{tile, x_pos, y_pos, true, nullptr});
	while(!q.empty())
	{
		Candidate* v = new Candidate(q.front());
		q.pop();
		if(v->tile->get_pos() == end_pos)
		{
			Candidate* x = v;
			std::cout << "we found the end!!!!" << v->tile->get_pos() << std::endl;
			this->nodes.push(*x);
			return;
		}
		std::vector<Candidate*> adjacents;
		if(v->x_pos > 0)
		{
			if(final_cands[v->y_pos][v->x_pos - 1].tile->get_size() == Fvec(-1, -1))
			{
				adjacents.push_back(&final_cands[v->y_pos][v->x_pos - 1]);
			}
		}
		if(v->x_pos + 1 < final_cands[y_pos].size())
		{
			if(final_cands[v->y_pos][v->x_pos + 1].tile->get_size() == Fvec(-1, -1))
			{
				adjacents.push_back(&final_cands[v->y_pos][v->x_pos + 1]);
			}
		}
		if(v->y_pos > 0)
		{
			if(final_cands[v->y_pos - 1][v->x_pos].tile->get_size() == Fvec(-1, -1))
			{
				adjacents.push_back(&final_cands[v->y_pos - 1][v->x_pos]);
			}
		}
		if(v->y_pos + 1 < final_cands.size())
		{
			if(final_cands[v->y_pos + 1][v->x_pos].tile->get_size() == Fvec(-1, -1))
			{
				adjacents.push_back(&final_cands[v->y_pos + 1][v->x_pos]);
			}
		}
		for(Candidate* c : adjacents)
		{
			if((int)c->x_pos <= map->get_tile_count().x && (int)c->y_pos <= map->get_tile_count().y)
			{
				if(!c->checked)
				{
					c->checked = true;
					c->parent = v;
					q.push(*c);
				}
			}
		}
	}
}
