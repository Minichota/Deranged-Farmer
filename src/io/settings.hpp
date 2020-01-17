#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <string>
#include <vector>

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

extern std::vector<Data<int>*> all;
Data<int>* get_setting(std::vector<Data<int>*>& data, std::string name);
}

#endif
