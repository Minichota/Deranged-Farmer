#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <vector>
#include <string>

namespace Settings
{
	/*
	   TODO Add more settings
	   Audio,
	   Video,
	   Keybindings
	*/
	template <class T>
	struct Data
	{
		std::string name;
		T data;
	};

	extern Data<int> volume;
	extern Data<int> iq;
	extern std::vector<Data<int>*> all;
}

#endif
