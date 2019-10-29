#include "tile.hpp"
#include "error.hpp"

Tile::Tile(SDL_Renderer* renderer, Ivec pos, Ivec size, Fvec scale):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = scale;
}

Tile::Tile(SDL_Renderer* renderer, Ivec pos, Ivec size):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
	this->scale = Fvec(1.0f,1.0f);
}

Tile::~Tile()
{
}

void Tile::update()
{
	this->rect =
	{
		(int)std::round(pos.x/scale.x),
		(int)std::round(pos.y/scale.y),
		size.x,
		size.y
	};
	this->src_rect =
	{
		(int)std::round(relative_pos.x/scale.x),
		(int)std::round(relative_pos.y/scale.y),
		size.x,
		size.y
	};
}

void Tile::render()
{
	SDL_RenderSetScale(renderer, scale.x, scale.y);
	SDL_RenderCopy(renderer, full_texture, &src_rect, &rect);
	SDL_RenderSetScale(renderer, 1.0f, 1.0f);
}

void Tile::load_texture(const char* file_path, Ivec relative_pos)
{
	this->full_texture = IMG_LoadTexture(renderer, file_path);
	Error(!full_texture, {"Failed to load image: ", file_path});
}

void Tile::set_texture(SDL_Texture* texture, Ivec relative_pos)
{
	this->full_texture = texture;
	this->relative_pos = relative_pos;
}

SDL_Texture* Tile::get_texture()
{
	return this->full_texture;
}
