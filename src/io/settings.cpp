#include <iostream>

#include "error.hpp"
#include "settings.hpp"

std::vector<Settings::Data<int>*> Settings::all;

Settings::Data<int>*
Settings::get_setting(std::vector<Settings::Data<int>*>& data, std::string name)
{
	for(Settings::Data<int>* d : data)
	{
		if(d->name == name)
		{
			return d;
		}
	}
	data.push_back(new Settings::Data<int>{ name, 0 });
	Error(true, { "Created missing setting: ", name.c_str() });
	return data.back();
}
