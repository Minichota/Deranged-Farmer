#include <SDL2/SDL_image.h>

#include "animation.hpp"
#include "game.hpp"
#include "interpolators.hpp"
#include "util.hpp"

Animation::Animation(SDL_Renderer* renderer, Sized<float>* parent,
					 std::string file_name, Ivec frame_size, long long delay) :
renderer(renderer),
parent(parent), file_name(file_name), frame_size(frame_size), delay(delay)
{
}

Animation::~Animation()
{
	clear();
}

void Animation::render()
{
	SDL_Rect src{ frame_pos[curr_frame].x, frame_pos[curr_frame].y,
				  frame_size.x, frame_size.y };
	SDL_Rect dst{ (int)std::round(parent->get_pos().x),
				  (int)std::round(parent->get_pos().y), frame_size.x,
				  frame_size.y };

	SDL_RenderSetScale(renderer, parent->get_scale().x, parent->get_scale().y);
	SDL_RenderCopyEx(renderer, master_frame, &src, &dst, parent->get_rotation(),
					 NULL, SDL_FLIP_NONE);
	static float enabled = 0;
	static Sized<float>* x;
	Game::debug->push_render(x, "Hitbox", { &enabled });
	if(enabled)
	{
		dst.x = (int)std::round(parent->get_collision_pos().x),
		dst.y = (int)std::round(parent->get_collision_pos().y),
		SDL_RenderDrawRect(renderer, &dst);
	}
	clear_render_settings(renderer);
}

void Animation::init()
{
	/*
	img(64,32) ->
	-> texture[]
	{
		(32,32),(32,32)
	}
	*/
	{
		master_frame = IMG_LoadTexture(renderer, file_name.c_str());
		Error{ master_frame == nullptr, { "Failed to load animation" }, true };
	}
	Ivec dimensions;
	SDL_QueryTexture(master_frame, NULL, NULL, &dimensions.x, &dimensions.y);
	size_t num_frames = dimensions.x / frame_size.x;
	for(size_t i = 0; i < num_frames; i++)
	{
		frame_pos.push_back(Ivec(i * frame_size.x, 0));
	}
	int_interpolaters.push_back(Interpolator<int>{
		REPEATER, &curr_frame, 0, ((int)num_frames - 1), delay });
}

void Animation::clear()
{
	SDL_DestroyTexture(master_frame);
	frame_pos.clear();
}

long long Animation::get_delay()
{
	return this->delay;
}
