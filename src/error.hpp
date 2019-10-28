#ifndef ERROR_HPP
#define ERROR_HPP

#include <vector>

class Error
{
	public:
	Error(bool condition, std::vector<const char*> message, bool game_ending = false);
	~Error();

	private:
	bool condition;
	std::vector<const char*> message;
	bool game_ending;
};
#endif
