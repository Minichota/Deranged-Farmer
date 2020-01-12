#include <iostream>

#include "error.hpp"
#include "game.hpp"
#include "io.hpp"

std::string read(const char* file_path)
{
	// load settings
	std::ifstream read(file_path);
	Error(!read, { "failed to load file: ", file_path });
	std::string buffer(std::istreambuf_iterator<char>(read), {});
	read.close();
	return buffer;
}

void write(const char* file_path, std::string& data)
{
	std::ofstream write(file_path);
	Error(!write, { "file does not exist: ", file_path });
	if(!write)
	{
		return;
	}
	write << data;
	Game::debug->push_log({ "wrote to file: ", file_path });
	write.close();
}
