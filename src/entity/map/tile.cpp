#include "tile.hpp"
#include "error.hpp"
#include "game.hpp"

Tile::Tile(SDL_Renderer* renderer, Fvec pos, Fvec size):
Renderable(renderer),
Sized(pos, size, Fvec(1.0f, 1.0f))
{
}

Tile::Tile():
Renderable(nullptr),
Sized(-1, -1, -1, -1, 1.0f, 1.0f)
{
}

Tile::~Tile()
{
}

void Tile::update()
{
	this->rect =
	{
		(int)std::round(pos.x),
		(int)std::round(pos.y),
		(int)std::round(size.x),
		(int)std::round(size.y),
	};
	this->src_rect =
	{
		(int)std::round(relative_pos.x),
		(int)std::round(relative_pos.y),
		(int)std::round(size.x),
		(int)std::round(size.y),
	};
}

void Tile::render()
{
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

void Tile::load_texture(const char* file_path, Ivec relative_pos)
{
	this->relative_pos = relative_pos;
	if(renderer!=nullptr)
	{
		// don't copy texture if tile is NULL
		this->full_texture = IMG_LoadTexture(renderer, file_path);
		Error(full_texture == nullptr, {"Failed to load image: ", file_path});
	}
}

void Tile::set_texture(SDL_Texture* texture, Ivec relative_pos)
{
	if(renderer!=nullptr)
	{
		// don't set texture if tile is NULL
		this->full_texture = texture;
	   	this->relative_pos = relative_pos;
	}
}

SDL_Texture* Tile::get_texture()
{
	return this->full_texture;
}

bool Tile::is_null()
{
	return renderer == nullptr;
}
