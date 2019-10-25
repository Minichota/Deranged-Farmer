#include "ui-base.hpp"

class UI_Image : public UI_Base
{
	public:
	UI_Image(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, Fill_Type fill_type, std::string file_path);
	~UI_Image();

	void update();
	void render();

	private:
	Fill_Type fill_type;

	SDL_Texture* texture;
	SDL_Rect output_rect;
};
