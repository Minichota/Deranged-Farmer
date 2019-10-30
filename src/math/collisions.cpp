#include "collisions.hpp"

bool Collision::test_collision_movingAA(Ivec& lhs_pos, Ivec lhs_size, Ivec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size)
{
	return true;
}

bool Collision::test_collision_movingAABB(Ivec& lhs_pos, Ivec lhs_size, Ivec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Ivec& rhs_vel)
{
	return false;
}

void Collision::handle_collision(Ivec& lhs_pos, Ivec lhs_size, Ivec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Ivec& rhs_vel)
{
}
