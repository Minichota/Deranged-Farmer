#include "tile.hpp"
#include "error.hpp"
#include "game.hpp"

Tile::Tile(SDL_Renderer* renderer, Fvec pos, Fvec size):
Renderable(renderer)
{
	this->pos = pos;
	this->size = size;
}

Tile::Tile():
Renderable(nullptr)
{
	this->pos = Fvec(-1, -1);
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
	SDL_RenderCopy(renderer, full_texture, &src_rect, &rect);
	if(Game::debug->active)
	{
		if(renderer != nullptr)
		{
		//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		//	SDL_RenderDrawRect(renderer, &rect);
		//	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			Game::debug->push_render(this, "Tile", { &this->pos, &this->size });
		}
	}
}

void Tile::load_texture(const char* file_path, Ivec relative_pos)
{
	this->relative_pos = relative_pos;
	{
		this->full_texture = IMG_LoadTexture(renderer, file_path);
		Error(full_texture == nullptr, {"Failed to load image: ", file_path});
	}
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

Fvec& Tile::get_pos()
{
	return this->pos;
}
