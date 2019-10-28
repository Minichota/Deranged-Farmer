#include "renderable.hpp"
#include "vectors.hpp"
#include "event-handler.hpp"

class Entity : public Renderable, public Event_Handler
{
	public:
	Entity(Ivec pos, Ivec size, Fvec scale);
	virtual ~Entity();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void handle_event(SDL_Event event) = 0;

	void set_texture(SDL_Texture* texture);
	SDL_Texture* get_texture();

	void set_pos(Ivec pos);
	Ivec& get_pos();

	void set_size(Ivec size);
	Ivec& get_size();

	void set_scale(Fvec size);
	Fvec& get_scale();

	protected:
	Ivec pos;
	Ivec size;
	Fvec scale;

	SDL_Texture* texture;
};
