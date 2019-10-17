#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>

#include "renderable.hpp"

template <class T>
class Animation
{
	public:
	Animation(T value_1, T value_2):
	value_1(value_1),
	value_2(value_2)
	{
	};
	~Animation()
	{
	};

	protected:
	const T value_1, value_2;
};
#endif
