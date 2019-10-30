#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "vectors.hpp"

namespace Collision
{
	static bool test_collision_movingAA(Ivec& lhs_pos, Ivec lhs_size, Ivec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size);
	static bool test_collision_movingAABB(Ivec& lhs_pos, Ivec lhs_size, Ivec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Ivec& rhs_vel);
	static void handle_collision(Ivec& lhs_pos, Ivec lhs_size, Ivec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Ivec& rhs_vel);
};
#endif
