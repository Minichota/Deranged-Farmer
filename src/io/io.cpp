#include <iostream>

#include "io.hpp"
#include "error.hpp"

std::string read(const char* file_path)
{
	// load settings
	std::ifstream read(file_path);
	Error e(!read, {"failed to load file: ", file_path});
	std::string buffer(std::istreambuf_iterator<char>(read), {});
	read.close();
	return buffer;
}
