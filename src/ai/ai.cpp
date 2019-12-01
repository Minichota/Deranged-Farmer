#include "ai.hpp"

AI::AI(Map& map, Entity* parent):
map(map)
{
	this->parent = parent;
}

AI::~AI()
{
}

Fvec AI::normalize(Fvec pos, Ivec& tile_size)
{
	/*
	   (322, 322)
 	   322 - (322 % 32)
 	   322 - (322 % 32 (==2))
	   -> (320,320)
	*/
	return Fvec(pos.x - ((int)std::round(pos.x) % tile_size.x),
				pos.y - ((int)std::round(pos.y) % tile_size.y));
}
