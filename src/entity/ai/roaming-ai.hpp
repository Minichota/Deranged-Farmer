#ifndef ROAMING_AI
#define ROAMING_AI

#include "ai.hpp"

class Roaming_AI : public AI
{
	public:
	Roaming_AI(Entity* parent, Map* map, const float radius, const long delay_of_movements);
	~Roaming_AI();

	void update();

	protected:
	void calculate_path();

	private:
	const float radius;
	const long delay_of_movements;
	long prev_time;
};
#endif
