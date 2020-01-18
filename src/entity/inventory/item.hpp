#ifndef ITEM_HPP
#define ITEM_HPP

#include <SDL2/SDL.h>

#include "animation.hpp"
#include "renderable.hpp"
#include "sized.hpp"
#include "vectors.hpp"

class Level;

enum Vim_Key
{
	H,
	J,
	K,
	L
};

class Item : public Renderable, public Sized<float>
{
	public:
	Item(SDL_Renderer* renderer, Sized<float>* parent, Ivec pos,
		 std::string icon_path, std::string animation_path, int type);
	~Item();

	void update();
	void render();

	void use(const Vim_Key key);

	void set_e_pos(Ivec pos);

	int get_type();

	private:
	Animation* animation;
	SDL_Texture* texture;
	Sized<float>* parent;
	Ivec offset;

	Ivec pos_2;

	bool swinging;

	long long start_time;

	int type;
};

#endif
