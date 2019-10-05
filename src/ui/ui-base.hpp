#include "vectors.hpp"
#include "renderable.hpp"

class UI_Base : public Renderable
{
	public:
	UI_Base(SDL_Texture* world_texture, Ivec pos, Ivec size, Fvec scale = Fvec(1.0,1.0));
	virtual ~UI_Base();

	virtual void update() = 0;
	virtual void render() = 0;

	protected:
	Ivec pos;
	Ivec size;
	Fvec scale;
};
