#ifndef AI_HPP
#define AI_HPP

#include <stack>

#include "entity.hpp"
#include "map.hpp"

class AI
{
	public:
	AI(Entity* parent, Map* map);
	virtual ~AI();

	virtual void update();

	protected:
	virtual void calculate_path();

	private:
	void push_node(Fvec node);
	Fvec pop_node();

	protected:
	Entity* parent;
	Map* map;

	Fvec next_pos;
	Fvec end_pos;

	bool completed_movement;

	private:
	std::stack<Fvec> nodes;
};
#endif
