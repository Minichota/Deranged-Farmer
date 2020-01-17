#ifndef AI_HPP
#define AI_HPP

#include "entity.hpp"
#include "map.hpp"

struct Position
{
	Ivec index = Ivec(-1.0f, -1.0f);
	Fvec pos = Fvec(-1.0f, -1.0f);
	bool null = false;
	bool checked = false;
	Position* parent = nullptr;
};

class AI
{
	public:
	AI(Map& map, Entity* parent);
	virtual ~AI();

	virtual void update() = 0;

	virtual bool generate_path() = 0;

	protected:
	Fvec normalize(Fvec pos, Ivec& tile_size);

	protected:
	Fvec goal_position;

	Map& map;
	Entity* parent;

	Position* pos;

	long long last_time;
	// if entity has not moved in threshold time, reset
	long long threshold = 1000;
};

#endif
