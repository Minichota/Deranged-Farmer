#include "ui-health_bar.hpp"

UI_Health_Bar::UI_Health_Bar(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale, SDL_Color border_color, SDL_Color bar_color, int* health, int max_health):
UI_Base(renderer, pos, size, scale, border_color),
border(renderer, pos, size, scale, border_color, NORMAL),
bar(renderer, pos, size, scale, bar_color, FILL)
{
	this->health = health;
	this->max_health = max_health;
	this->bar_color = bar_color;
}

UI_Health_Bar::~UI_Health_Bar()
{
}

void UI_Health_Bar::update()
{
	this->bar.set_size(Ivec(size.x*(*health)/max_health, size.y));
	bar.update();
	border.update();
}

void UI_Health_Bar::render()
{
	bar.render();
	border.render();
}

void UI_Health_Bar::set_origin(Ivec origin)
{
	border.set_origin(origin);
	bar.set_origin(origin);
}
