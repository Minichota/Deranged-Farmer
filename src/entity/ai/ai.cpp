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
