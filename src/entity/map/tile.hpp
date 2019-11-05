#ifndef TILE_HPP
#define TILE_HPP

#include "vectors.hpp"
#include "renderable.hpp"

class Tile : public Renderable
{
	public:
	Tile(SDL_Renderer* renderer, Fvec pos, Fvec size, Fvec scale);
	Tile(SDL_Renderer* renderer, Fvec pos, Fvec size);
	Tile();
	~Tile();

	void update();
	void render();

	void load_texture(const char* file_path, Ivec relative_pos);
	void set_texture(SDL_Texture* texture, Ivec relative_pos);
	SDL_Texture* get_texture();

	Fvec& get_pos();

	private:
	Fvec pos;
	Fvec size;
	Fvec scale;

	SDL_Texture* full_texture;
	Ivec relative_pos;

	SDL_Rect rect;
	SDL_Rect src_rect;
};
#endif
