#ifndef AI_HPP
#define AI_HPP

#include <stack>

#include "entity.hpp"
#include "map.hpp"

struct Candidate
{
	Tile* tile;
	size_t x_pos;
	size_t y_pos;
	bool checked = false;
	Candidate* parent;
};

class AI
{
	public:
	AI(Entity* parent, Map* map);
	virtual ~AI();

	virtual void update();

	protected:
	virtual void calculate_path();

	protected:
	Entity* parent;
	Map* map;

	Fvec next_pos;
	Fvec end_pos;

	bool completed_movement;

	std::stack<Candidate> nodes;
};
#endif
