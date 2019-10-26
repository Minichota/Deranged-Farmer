#include "settings.hpp"

int Settings::volume;
int Settings::iq;
std::vector<int*> Settings::all
{
	&Settings::volume,
	&Settings::iq
};
