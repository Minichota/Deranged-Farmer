#ifndef TILE_HPP
#define TILE_HPP

#include "renderable.hpp"
#include "sized.hpp"
#include "vectors.hpp"

class Tile : public Renderable, public Sized<float>
{
	public:
	Tile(SDL_Renderer* renderer, Fvec pos, Fvec size);
	~Tile();

	void update();
	void render();

	void set_relative_pos(Ivec new_pos);
	Ivec& get_relative_pos();

	bool is_null();
	void set_renderer(SDL_Renderer* renderer);

	private:
	Ivec relative_pos;
};

extern SDL_Texture* full_texture;
void load_tileset(SDL_Renderer* renderer, const char* file_path);
SDL_Texture* get_texture();
#endif
