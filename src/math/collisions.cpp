#include "collisions.hpp"

bool test_collision_movingAA(Ivec lhs_pos, Ivec lhs_size, Fvec lhs_vel, Ivec rhs_pos, Ivec rhs_size)
{
	Ivec lhs_bottom_right = lhs_pos + lhs_size;
	return lhs_pos.x <= rhs_pos.x &&
		   rhs_pos.x <= lhs_bottom_right.x &&
		   lhs_pos.y <= rhs_pos.y &&
		   rhs_pos.y <= lhs_bottom_right.y;
}

bool test_collision_movingAABB(Ivec& lhs_pos, Ivec lhs_size, Fvec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Fvec& rhs_vel)
{
	return true;
}

void handle_collision_movingAA(Ivec& lhs_pos, Ivec lhs_size, Fvec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size)
{
	float lhs_bottom = lhs_pos.y + lhs_size.y;
	float rhs_bottom = rhs_pos.y + rhs_size.y;
	float lhs_right = lhs_pos.x + lhs_size.x;
	float rhs_right = rhs_pos.x + rhs_size.x;

	float b_collision = rhs_bottom - lhs_pos.y;
	float t_collision = lhs_bottom - rhs_pos.y;
	float l_collision = lhs_right - rhs_pos.x;
	float r_collision = rhs_right - lhs_pos.x;

	std::cout << rhs_pos << rhs_size << lhs_pos << lhs_size << std::endl;

	if (t_collision < b_collision && t_collision < l_collision && t_collision < r_collision )
	{
	//Top collision
		std::cout << "up collision" << std::endl;
		//lhs_vel.y = -3.0f;
	}
	if (b_collision < t_collision && b_collision < l_collision && b_collision < r_collision)
	{
	//bottom collision
		std::cout << "down collision" << std::endl;
		//lhs_vel.y = 3.0f;
	}
	if (l_collision < r_collision && l_collision < t_collision && l_collision < b_collision)
	{
	//Left collision
		std::cout << "left collision" << std::endl;
		//lhs_vel.x = -3.0f;
	}
	if (r_collision < l_collision && r_collision < t_collision && r_collision < b_collision )
	{
	//Right collision
		std::cout << "right collision" << std::endl;
		//lhs_vel.x = 3.0f;
	}
}

void handle_collision_movingAABB(Ivec& lhs_pos, Ivec lhs_size, Fvec& lhs_vel, Ivec& rhs_pos, Ivec rhs_size, Fvec& rhs_vel)
{
}
