#ifndef CONSOLE_LOG_HPP
#define CONSOLE_LOG_HPP

#include <string>

class Console_Log
{
	public:
	Console_Log(std::string text, long long life_time);
	~Console_Log();

	bool get_active();

	std::string& get_text();

	private:
	std::string text;
	long long spawn_time;
	long long life_time;
};

#endif
