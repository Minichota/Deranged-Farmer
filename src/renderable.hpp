#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>

class Renderable
{
	public:
	Renderable(SDL_Renderer* renderer);
	virtual ~Renderable();

	virtual void update() = 0;
	virtual void render() = 0;

	protected:
	SDL_Renderer* renderer;
};
#endif
