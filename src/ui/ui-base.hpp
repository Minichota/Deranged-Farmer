#ifndef UI_BASE_HPP
#define UI_BASE_HPP

#include "vectors.hpp"
#include "renderable.hpp"

typedef enum
{
	FILL,
	NORMAL
} Fill_Type;

class UI_Base : public Renderable
{
	public:
	UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale = Fvec(1.0,1.0), SDL_Color color = {});
	UI_Base(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale = Fvec(1.0,1.0));
	virtual ~UI_Base();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void set_color(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t alpha = 255);
	virtual void set_color(SDL_Color color);
	SDL_Color& get_color();

	virtual void set_abs_pos(Ivec pos);
	virtual Ivec& get_abs_pos();

	virtual Ivec get_pos();

	virtual void set_size(Ivec size);
	virtual Ivec& get_size();

	virtual void set_scale(Fvec scale);
	virtual Fvec& get_scale();

	virtual void set_origin(Ivec origin);
	virtual Ivec& get_origin();

	protected:
	virtual bool in_bounds(Ivec input_pos);

	protected:
	Ivec pos;
	Ivec size;
	Fvec scale;
	Ivec origin = Ivec(0,0);

	SDL_Color color;
};
#endif
