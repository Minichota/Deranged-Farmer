#ifndef AI_HPP
#define AI_HPP

#include <queue>

#include "map.hpp"
#include "entity.hpp"

struct Position
{
	Ivec index;
	Fvec pos;
	bool null;
	bool checked = false;
	Position* parent;
};

class AI
{
	public:
	AI(Map& map, Entity* parent);
	virtual ~AI();

	virtual void update() = 0;

	virtual void generate_path() = 0;

	protected:
	Fvec normalize(Fvec pos, Ivec& tile_size);

	protected:
	Fvec goal_position;

	Map& map;
	Entity* parent;

	Position pos;
	Fvec next_pos = Fvec(1.0f, 1.0f);

	long long last_time;
	// if entity has not moved in threshold time, reset
	long long threshold = 1000;
};

#endif
