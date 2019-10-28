#include "settings.hpp"

Settings::Setting<int> Settings::volume =
{
	"volume"
};
Settings::Setting<int> Settings::iq =
{
	"iq"
};
std::vector<Settings::Setting<int>*> Settings::all
{
	&Settings::volume,
	&Settings::iq
};
