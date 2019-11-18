#ifndef UI_TEXT_HPP
#define UI_TEXT_HPP

#include <SDL2/SDL_ttf.h>

#include "ui-base.hpp"

class UI_Text : public UI_Base
{
	public:
	UI_Text(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, std::string text, std::string font_path, SDL_Color font_color, Fill_Type type);
	~UI_Text();

	void update();
	void render();

	void reload_texture();

	void set_text(std::string text);
	void append_text(std::string text);
	void clear();

	std::string get_text();
	Ivec& get_size();

	void set_font_size(int font_size);

	private:
	Fill_Type type;

	Ivec tex_size;
	Ivec actual_size;

	std::string prev_text;
	std::string text;

	TTF_Font* font;
	std::string font_path;
	SDL_Color font_color;
	int font_height;

	SDL_Texture* output;
};
#endif
