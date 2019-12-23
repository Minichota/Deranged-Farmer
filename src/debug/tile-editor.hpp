#ifndef TILE_EDITOR_HPP
#define TILE_EDITOR_HPP

#include <SDL2/SDL.h>

#include "renderable.hpp"
#include "ui-text-input.hpp"
#include "tile.hpp"

class Map;

class Tile_Editor : public Renderable, public Event_Handler
{
	public:
	Tile_Editor(SDL_Renderer* renderer);
	~Tile_Editor();

	void update();
	void render();

	void clear();

	void handle_event(const SDL_Event& event);

	void set_map(Map* map);

	public:
	bool active;

	private:
	Tile* hovered_tile();

	private:
	Map* map;

	Ivec tile_size;

	Ivec cursor_pos;

	Ivec sel_type;
};

#endif
