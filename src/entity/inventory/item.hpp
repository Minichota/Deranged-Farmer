#ifndef ITEM_HPP
#define ITEM_HPP

#include <SDL2/SDL.h>

#include "vectors.hpp"
#include "renderable.hpp"

class Level;

class Item : public Renderable
{
	public:
	Item(SDL_Renderer* renderer, Level* level, Ivec pos, std::string file_path);
	~Item();

	void update();
	void render();

	void use();
	void pick();

	Ivec get_pos();
	void set_pos(Ivec pos);
	Ivec get_size();

	private:
	Level* level;
	SDL_Texture* texture;

	Ivec pos;

	bool dropped;
};

#endif
