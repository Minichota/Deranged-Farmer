#include "settings.hpp"

Settings::Data<int> Settings::volume =
{
	"volume"
};
Settings::Data<int> Settings::iq =
{
	"iq"
};
std::vector<Settings::Data<int>*> Settings::all
{
	&Settings::volume,
	&Settings::iq
};
