#ifndef IO_HPP
#define IO_HPP

#include <fstream>

#include "settings.hpp"
#include "error.hpp"

std::string read(const char* file_path);

template <class T>
static void parse(std::string data, const char delimiter, std::vector<Settings::Setting<T>*>& values)
{
	std::string curr_data;
	bool start_parsing = false;
	// find occurance of data
	for(size_t i = 0; i < values.size(); i++)
	{
		size_t pos = data.find(values[i]->name);
		if(pos != std::string::npos)
		{
			bool cont = true;
			// iterate through to find data
			for(size_t j = pos; j < data.size(); j++)
			{
				if(!cont)
					break;
				if(data[j] == delimiter)
				{
					start_parsing = true;
					j++;
				}
				switch(data[j])
				{
					case '\n':
					{
						// end of line
						if(start_parsing)
						{
							values[i]->data = std::stoi(curr_data);
							start_parsing = false;
							curr_data.clear();
							cont = false;
						}
					} break;
					default:
					{
						if(start_parsing && data[j] != ' ')
						{
							curr_data.push_back(data[j]);
						}
					} break;
				}
			}
		}
	}
}

template <class T>
static void write(const char* file_path, std::vector<Settings::Setting<T>*> data)
{
	std::ofstream write(file_path);
	Error(!write, {"failed to write to file:", file_path});
	for(size_t i = 0; i < data.size(); i++)
	{
		write << data[i]->name << " = " << data[i]->data << '\n';
	}
	write.close();
}

#endif
