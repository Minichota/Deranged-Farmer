#ifndef UI_Rect_HPP
#define UI_Rect_HPP

#include "ui-base.hpp"

typedef enum
{
	FILL,
	BORDER
} Fill_Type;

class UI_Rect : public UI_Base
{
	public:
	UI_Rect(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color color, Fill_Type type);
	~UI_Rect();

	void update();
	void render();

	private:
	Fill_Type type;
	SDL_Rect sprite;
};

#endif
