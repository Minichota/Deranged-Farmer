#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "vectors.hpp"

bool test_collision_movingAA(Ivec lhs_pos, Ivec lhs_size, Fvec lhs_vel, Ivec rhs_pos, Ivec rhs_size);
bool test_collision_movingAABB(Ivec lhs_pos, Ivec lhs_size, Fvec lhs_vel, Ivec rhs_pos, Ivec rhs_size, Fvec rhs_vel);
void handle_collision_movingAA(Ivec& lhs_pos, Ivec lhs_size, Fvec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size);
void handle_collision_movingAABB(Ivec& lhs_pos, Ivec lhs_size, Fvec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Fvec& rhs_vel);
#endif
