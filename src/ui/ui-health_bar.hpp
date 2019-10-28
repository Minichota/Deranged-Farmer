#include "ui-base.hpp"
#include "ui-rect.hpp"
#include "ui-text.hpp"

class UI_Health_Bar : public UI_Base
{
	public:
	UI_Health_Bar(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color border_color, SDL_Color bar_color, int* health, int max_health);
	~UI_Health_Bar();

	void update();
	void render();

	void set_origin(Ivec origin);

	private:
	UI_Rect border;
	UI_Rect bar;

	SDL_Color bar_color;

	int* health;
	int max_health;
};
