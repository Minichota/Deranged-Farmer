#ifndef AI_ROAMING_HPP
#define AI_ROAMING_HPP

#include "ai.hpp"

class AI_Roaming : public AI
{
	public:
	AI_Roaming(Map& map, Entity* parent, long long delay);

	void update();

	bool generate_path();

	private:
	long long delay;
	long long prev_location;
	bool done;
};

#endif
