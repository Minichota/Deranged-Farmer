#include "tile.hpp"
#include "error.hpp"
#include "game.hpp"

SDL_Texture* full_texture = nullptr;

Tile::Tile(SDL_Renderer* renderer, Fvec pos, Fvec size):
Renderable(renderer),
Sized(pos, size, Fvec(1.0f, 1.0f))
{
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render()
{
	SDL_Rect rect =
	{
		(int)pos.x,
		(int)pos.y,
		(int)size.x,
		(int)size.y,
	};

	SDL_Rect src_rect =
	{
		(int)relative_pos.x,
		(int)relative_pos.y,
		(int)size.x,
		(int)size.y,
	};

	if(renderer!=nullptr)
	{
		SDL_RenderCopy(renderer, full_texture, &src_rect, &rect);
		if(Game::debug->active)
		{
			Game::debug->push_render(this, "Tile", {});
		}
	}
	if(Game::debug->active)
	{
		Game::debug->push_rect(this->pos,
							   this->size);
	}
}

void load_tileset(SDL_Renderer* renderer, const char* file_path)
{
	std::cout << "loaded tileset" << std::endl;
	if(full_texture != nullptr)
	{
		SDL_DestroyTexture(full_texture);
	}
	full_texture = IMG_LoadTexture(renderer, file_path);
	Error(full_texture == nullptr, {"Failed to load tileset: ", file_path});
}

void Tile::set_relative_pos(Ivec new_pos)
{
	this->relative_pos = new_pos;
}

SDL_Texture* get_texture()
{
	return full_texture;
}

bool Tile::is_null()
{
	return renderer == nullptr;
}

void Tile::set_renderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}
