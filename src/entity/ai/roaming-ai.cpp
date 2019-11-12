#include "game.hpp"
#include "roaming-ai.hpp"

Roaming_AI::Roaming_AI(Entity* parent, Map* map, const float radius, const long delay_of_movements):
AI(parent, map),
radius(radius),
delay_of_movements(delay_of_movements)
{
	prev_time = 0;
}

Roaming_AI::~Roaming_AI()
{
}

void Roaming_AI::update()
{
	if(SDL_GetTicks() - prev_time >= delay_of_movements && completed_movement)
	{
		prev_time = SDL_GetTicks();
		float r = radius * sqrt(rand());
		float theta = rand() * 2 * 3.1415926f;

		end_pos.x = parent->get_pos().x + parent->get_size().x / 2 + r * cosf(theta);
		end_pos.y = parent->get_pos().y + parent->get_size().y / 2 + r * sinf(theta);

		if(Game::debug->active)
		{
			Game::debug->push_console(end_pos.x);
			Game::debug->push_console(end_pos.y);
		}
		calculate_path();
	}
}

void Roaming_AI::calculate_path()
{
	//std::vector<Fvec> candidates = map->get_empty_tiles();
}
