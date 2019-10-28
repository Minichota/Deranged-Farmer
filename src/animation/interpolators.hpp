#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <variant>
#include <iostream>
#include <cassert>

#include "renderable.hpp"
#include "vectors.hpp"

typedef enum
{
	OSCILLATOR,
	REPEATER
} Interpolator_Type;

template <class T>
struct Interpolator
{
	Interpolator_Type type;
	T* actual_value;
	T min_value;
	T max_value;
	long delay_1;
	long delay_2;
	bool* flag;
};

void update_interpolators();

template <class T>
void oscillate(Interpolator<T>& i)
{
	long curr_time = SDL_GetTicks();

	double delta_time = (curr_time % (i.delay_1 + i.delay_2));

	bool reverse_flag;
	// determine direction and dt
	if((reverse_flag = get_direction(i)))
	{
		delta_time -= i.delay_1;
	}

	double time_fraction = delta_time / (reverse_flag ? i.delay_2 : i.delay_1);

	T return_value = reverse_flag ? i.max_value : i.min_value;
	if(!reverse_flag)
	{
		return_value += (i.max_value - i.min_value) * time_fraction;
	}
	else
	{
		return_value -= (i.max_value - i.min_value) * time_fraction;
	}
	*i.actual_value = return_value;
}

template <class T>
void repeat(Interpolator<T>& i)
{
	long curr_time = SDL_GetTicks();

	long pos = curr_time % i.delay_1;

	*i.actual_value = i.min_value + (i.max_value - i.min_value) * (pos / (double)i.delay_1);
}

template <class T>
bool get_direction(Interpolator<T> i)
{
	// returns true if going backwards and false if going forwards
	long curr_time = SDL_GetTicks();
	return (curr_time % (i.delay_1 + i.delay_2)) > i.delay_1;
}

extern std::vector<Interpolator<float>> float_interpolaters;
extern std::vector<Interpolator<int>> int_interpolaters;
extern std::vector<Interpolator<unsigned char>> uchar_interpolaters;
extern std::vector<Interpolator<Ivec>> ivec_interpolaters;

#endif
