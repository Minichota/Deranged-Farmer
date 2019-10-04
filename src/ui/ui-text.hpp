#include <SDL2/SDL_ttf.h>

#include "ui-base.hpp"

class UI_Text : public UI_Base
{
	public:
	UI_Text(SDL_Texture* world_texture, Ivec pos, Ivec size, Fvec scale, std::string text = "");
	~UI_Text();

	void update();
	void render();

	private:
	std::string text;
};
