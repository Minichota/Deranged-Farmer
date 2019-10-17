#ifndef TIMER_ANIMATION_HPP
#define TIMER_ANIMATION_HPP

#include <iostream>

#include "animation.hpp"

template <class T>
class Timer_Animation : public Animation<T>
{
	public:
	Timer_Animation(T value_1, T value_2, long delay_1, long delay_2):
	Animation<T>(value_1, value_2),
	delay_1(delay_1),
	delay_2(delay_2)
	{
	}

	~Timer_Animation()
	{
	}

	T get_value()
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

		//std::cout << "delta time: " << delta_time << " delay_1 and delay_2: " << delay_1 << "  " << delay_2 << std::endl;

		double time_fraction = (double)delta_time / (reverse_flag ? delay_2 : delay_1);

		//std::cout << "time fraction: " << time_fraction << std::endl;

		T return_value = reverse_flag ? this->value_2 : this->value_1;
		if(!reverse_flag)
		{
			//std::cout << this->value_2 << this->value_1 << (this->value_2 - this->value_1)* time_fraction << std::endl;
			return_value += (this->value_2 - this->value_1) * time_fraction;
		}
		else
		{
			return_value -= (this->value_2 - this->value_1) * time_fraction;
		}
		return return_value;
	}

	private:
	const long delay_1, delay_2;
	long curr_time;
};

#endif
