#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <string>
#include <vector>

#include "entity.hpp"
#include "sized.hpp"
#include "vectors.hpp"

class Animation
{
	public:
	Animation(SDL_Renderer* renderer, Sized<float>* parent,
			  std::string file_name, Ivec frame_size, long long delay);
	~Animation();

	void render();

	void init();
	void clear();

	long long get_delay();

	private:
	SDL_Renderer* renderer;
	Sized<float>* parent;

	SDL_Texture* master_frame;
	std::vector<Ivec> frame_pos;
	std::string file_name;
	Ivec frame_size;
	long long delay;
	int curr_frame;
};

#endif
