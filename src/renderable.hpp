#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

class Renderable
{
	public:
	Renderable(SDL_Texture* world_texture);
	virtual ~Renderable();

	virtual void update() = 0;
	virtual void render() = 0;

	private:
	SDL_Texture* const world_texture;
};
#endif
