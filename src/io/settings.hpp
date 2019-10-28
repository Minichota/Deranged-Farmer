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
	struct Setting
	{
		std::string name;
		T data;
	};

	extern Setting<int> volume;
	extern Setting<int> iq;
	extern std::vector<Setting<int>*> all;
}

#endif
