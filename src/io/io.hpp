#ifndef IO_HPP
#define IO_HPP

#include <cctype>
#include <fstream>
#include <iostream>

#include "error.hpp"
#include "settings.hpp"

std::string read(const char* file_path);

template <class T>
void parse(std::string data, const char delimiter,
		   std::vector<Settings::Data<T>*>& values, int start_pos = 0,
		   int count = 1000)
{
	std::string curr_name;
	std::string curr_data;
	bool start_parsing = false;
	int iter_count = 0;
	// iterate through to find data
	for(size_t i = 0; i < data.size(); i++)
	{
		if(data[i] == delimiter)
		{
			start_parsing = true;
			i++;
		}
		switch(data[i])
		{
			case '\n':
			{
				// end of line
				if(curr_data.empty() || curr_name.empty())
				{
					start_parsing = false;
				}
				if(start_parsing)
				{
					if(iter_count - start_pos >= count)
					{
						return;
					}
					if(iter_count >= start_pos)
					{
						values.push_back(new Settings::Data<T>{
							curr_name, std::stoi(curr_data) });
					}
					start_parsing = false;
					iter_count++;
				}
				curr_data.clear();
				curr_name.clear();
			}
			break;
			default:
			{
				if(start_parsing && data[i] != ' ')
				{
					curr_data.push_back(data[i]);
				}
				else if(!start_parsing && data[i] != ' ')
				{
					curr_name.push_back(data[i]);
				}
			}
			break;
		}
	}
}

template <class T>
void parse_csv(std::string data, std::vector<std::vector<T>>& values,
			   int start_pos = 0, int count = 1000)
{
	std::string curr_data;
	int value_pos = 0;
	for(size_t i = 0; i < data.size(); i++)
	{
		switch(data[i])
		{
			case ',':
			{
				if(value_pos - start_pos >= count)
				{
					return;
				}
				if(value_pos - start_pos >= (int)values.size())
				{
					values.push_back(std::vector<int>());
				}
				if(value_pos >= start_pos)
				{
					values[value_pos - start_pos].push_back(
						std::stoi(curr_data));
				}
				curr_data.clear();
			}
			break;
			case '\n':
			{
				if(value_pos >= start_pos)
				{
					values[value_pos - start_pos].push_back(
						std::stoi(curr_data));
				}
				value_pos++;
				curr_data.clear();
			}
			break;
			default:
			{
				if(!std::isdigit(data[i]))
				{
					// skips other formatted lines
					while(i != data.size())
					{
						if(data[i] == '\n')
						{
							break;
						}
						i++;
					}
				}
				else if(data[i] != ' ')
				{
					curr_data.push_back(data[i]);
				}
			}
			break;
		}
	}
}

template <class T>
void write_settings(const char* file_path, std::vector<Settings::Data<T>*> data)
{
	std::ofstream write(file_path);
	Error(!write, { "failed to write to file:", file_path });
	for(size_t i = 0; i < data.size(); i++)
	{
		write << data[i]->name << " = " << data[i]->data << '\n';
	}
	write.close();
}

void write(const char* file_path, std::string& data);

#endif
