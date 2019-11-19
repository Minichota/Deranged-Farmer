#include "interpolators.hpp"

std::vector<Interpolator<float>> float_interpolaters;
std::vector<Interpolator<unsigned char>> uchar_interpolaters;
std::vector<Interpolator<int>> int_interpolaters;
std::vector<Interpolator<Ivec>> ivec_interpolaters;

void update_interpolators()
{
	for(Interpolator<float>& i : float_interpolaters)
	{
		switch(i.type)
		{
			case OSCILLATOR:
			{
				oscillate(i);
			} break;
			case REPEATER:
			{
				repeat(i);
			} break;
		}
	}

	for(Interpolator<unsigned char>& i : uchar_interpolaters)
	{
		switch(i.type)
		{
			case OSCILLATOR:
			{
				oscillate(i);
			} break;
			case REPEATER:
			{
				repeat(i);
			} break;
		}
	}

	for(Interpolator<int>& i : int_interpolaters)
	{
		switch(i.type)
		{
			case OSCILLATOR:
			{
				oscillate(i);
			} break;
			case REPEATER:
			{
				repeat(i);
			} break;
		}
	}

	for(Interpolator<Ivec>& i : ivec_interpolaters)
	{
		switch(i.type)
		{
			case OSCILLATOR:
			{
				oscillate(i);
			} break;
			case REPEATER:
			{
				repeat(i);
			} break;
		}
	}
}

void clear_interpolators()
{
	float_interpolaters.erase(float_interpolaters.begin(), float_interpolaters.end());
	uchar_interpolaters.erase(uchar_interpolaters.begin(), uchar_interpolaters.end());
	int_interpolaters.erase(int_interpolaters.begin(), int_interpolaters.end());
	ivec_interpolaters.erase(ivec_interpolaters.begin(), ivec_interpolaters.end());
}

