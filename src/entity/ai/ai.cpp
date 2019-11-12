#include "ai.hpp"

AI::AI(Entity* parent, Map* map)
{
	this->parent = parent;
	this->map = map;
}

AI::~AI()
{
}

void AI::update()
{
	// handles the entities direction and velocity
}

void AI::calculate_path()
{
	// runs until path is found
}

void AI::push_node(Fvec node)
{
	this->nodes.push(node);
}

Fvec AI::pop_node()
{
	Fvec top = nodes.top();
	nodes.pop();
	return top;
}
