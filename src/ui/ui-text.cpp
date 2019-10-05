#include "ui-text.hpp"

UI_Text::UI_Text(SDL_Texture* world_texture, Ivec pos, Ivec size, Fvec scale, std::string text):
UI_Base(world_texture, pos, size, scale)
{
	this->text = text;
}

UI_Text::~UI_Text()
{
	this->text.clear();
}

void UI_Text::update()
{
}

// TODO implement ui-text rendering
void UI_Text::render()
{
}
