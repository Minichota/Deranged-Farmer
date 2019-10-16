#ifndef UI_BASE_HPP
#define UI_BASE_HPP

#include "vectors.hpp"
#include "renderable.hpp"

class UI_Base : public Renderable
{
	public:
	UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale = Fvec(1.0,1.0), SDL_Color color = {});
	UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale = Fvec(1.0,1.0));
	virtual ~UI_Base();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void set_color(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t alpha = 255);

	protected:
	Ivec pos;
	Ivec size;
	Fvec scale;

	SDL_Color color;

	virtual bool in_bounds(Ivec input_pos);
};
#endif
