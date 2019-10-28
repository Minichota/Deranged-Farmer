#include <iostream>

#include "io.hpp"

std::string read(const char* file_path)
{
	// load settings
	std::ifstream read(file_path);
	if(!read)
	{
		std::cout << "failed to read file" << std::endl;
	}
	std::string buffer(std::istreambuf_iterator<char>(read), {});
	read.close();
	return buffer;
}
