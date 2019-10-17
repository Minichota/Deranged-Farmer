#ifndef TIMER_ANIMATION_HPP
#define TIMER_ANIMATION_HPP

#include <iostream>

#include "animation.hpp"

template <class T>
struct Oscillator
{
	T* actual_value;
	T min_value;
	T max_value;
};

template <class T>
class Oscillator_Animation : public Animation<T>
{
	public:
	Oscillator_Animation(T value_1, T value_2, long delay_1, long delay_2):
	Animation<T>(value_1, value_2),
	delay_1(delay_1),
	delay_2(delay_2)
	{
	}

	~Oscillator_Animation()
	{
		oscillators.clear();
	}

	bool get_direction()
	{
		// returns true if going backwards and false if going forwards
		curr_time = SDL_GetTicks();
		return (curr_time % (delay_1 + delay_2)) > delay_1;
	}

	void update()
	{
		curr_time = SDL_GetTicks();

		double delta_time;
		bool reverse_flag = false;

		// determine direction and dt
		if((delta_time = (curr_time % (delay_1 + delay_2))) > delay_1)
		{
			reverse_flag = true;
			delta_time -= delay_1;
		}

		double time_fraction = (double)delta_time / (reverse_flag ? delay_2 : delay_1);

		for(Oscillator o : oscillators)
		{
			T return_value = reverse_flag ? o.max_value : o.min_value;
			if(!reverse_flag)
			{
				return_value += (o.max_value - o.min_value) * time_fraction;
			}
			else
			{
				return_value -= (o.max_value - o.min_value) * time_fraction;
			}
			*o.actual_value = return_value;
		}
	}

	void push_oscillator(T* actual_value, T min_value, T max_value)
	{
		oscillators.push_back(Oscillator<T>{actual_value, min_value, max_value});
	}

	private:
	const long delay_1, delay_2;
	long curr_time;

	std::vector<Oscillator<T>> oscillators;
};

#endif
