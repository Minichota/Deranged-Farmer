#include "tile-editor.hpp"
#include "util.hpp"
#include "game.hpp"
#include "map.hpp"

Tile_Editor::Tile_Editor(SDL_Renderer* renderer):
Renderable(renderer)
{
	this->map = nullptr;
	cursor_pos = Ivec(0,0);
	clear();
}

Tile_Editor::~Tile_Editor()
{
}

void Tile_Editor::update()
{
	if(keys[SDL_SCANCODE_R])
	{
		Ivec tile_count = map->get_tile_count();
		if(cursor_pos.x < 0   || cursor_pos.y < 0 ||
		  (cursor_pos.x > 768 || cursor_pos.y > 576))
		{
			Game::debug->push_log({"Tile must be within map", "\n"});
			return;
		}

		Tile* old_tile = hovered_tile();

		old_tile->set_relative_pos(Ivec(sel_type.x * map->get_tile_size().x,
									   (sel_type.y * map->get_tile_size().y)));
		if(old_tile->is_null())
		{
			old_tile->set_renderer(renderer);
		}
	}
	if(keys[SDL_SCANCODE_X])
	{
		std::vector<std::vector<Tile*>>& tiles = map->get_tiles();
		tiles[cursor_pos.y/32][cursor_pos.x/32]->set_renderer(nullptr);
	}
}

void Tile_Editor::render()
{
	if(map != nullptr)
	{
		// draw cursor
		SDL_Rect rect =
		{ cursor_pos.x, cursor_pos.y, tile_size.x, tile_size.y };
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &rect);

		Ivec tex_size;
		SDL_QueryTexture(full_texture, NULL, NULL, &tex_size.x, &tex_size.y);
		// rendering of all tiles
		rect =
		{ (cursor_pos.x + tile_size.x) * 2, cursor_pos.y * 2, tex_size.x, tex_size.y };
		SDL_RenderSetScale(renderer, 0.5f,0.5f);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_SetTextureAlphaMod(full_texture, 150);
		SDL_RenderCopy(renderer, full_texture, NULL, &rect);
		SDL_SetTextureAlphaMod(full_texture, 255);
		SDL_RenderSetScale(renderer, 1.0f,1.0f);
		// highlighting of selected tile
		rect =
		{ cursor_pos.x + tile_size.x + sel_type.x * tile_size.x/2, cursor_pos.y + sel_type.y * tile_size.y/2, tile_size.x/2, tile_size.y/2 };
		SDL_RenderDrawRect(renderer, &rect);
		clear_render_settings(renderer);
	}
}

void Tile_Editor::clear()
{
	cursor_pos = Ivec(0,0);
	sel_type = Ivec(0,0);
	this->active = false;
}

void Tile_Editor::set_map(Map* map)
{
	this->map = map;
	this->tile_size = map->get_tile_size();
}

void Tile_Editor::handle_event(const SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_h:
				{
					if(keys[SDL_SCANCODE_LSHIFT])
					{
						sel_type.x--;
						Ivec tex_size;
						SDL_QueryTexture(full_texture, NULL, NULL, &tex_size.x, &tex_size.y);
						if(sel_type.x < 0)
						{
							sel_type.x = tex_size.x / 32 - 1;
						}
					}
					else
					{
						cursor_pos.x -= 32;
						if(cursor_pos.x < 0)
						{
							cursor_pos.x = 0;
						}
					}
				} break;
				case SDLK_j:
				{
					if(keys[SDL_SCANCODE_LSHIFT])
					{
						sel_type.y++;
						Ivec tex_size;
						SDL_QueryTexture(full_texture, NULL, NULL, &tex_size.x, &tex_size.y);
						if(sel_type.y >= tex_size.y / 32)
						{
							sel_type.y = 0;
						}
					}
					else
					{
						cursor_pos.y += 32;
						if(cursor_pos.y > 576)
						{
							cursor_pos.y = 576;
						}
					}
				} break;
				case SDLK_k:
				{
					if(keys[SDL_SCANCODE_LSHIFT])
					{
						sel_type.y--;
						Ivec tex_size;
						SDL_QueryTexture(full_texture, NULL, NULL, &tex_size.x, &tex_size.y);
						if(sel_type.y < 0)
						{
							sel_type.y = tex_size.y / 32 - 1;
						}
					}
					else
					{
						cursor_pos.y -= 32;
						if(cursor_pos.y < 0)
						{
							cursor_pos.y = 0;
						}
					}
				} break;
				case SDLK_l:
				{
					if(keys[SDL_SCANCODE_LSHIFT])
					{
						sel_type.x++;
						Ivec tex_size;
						SDL_QueryTexture(full_texture, NULL, NULL, &tex_size.x, &tex_size.y);
						if(sel_type.x >= tex_size.x / 32)
						{
							sel_type.x = 0;
						}
					}
					else
					{
						cursor_pos.x += 32;
						if(cursor_pos.x > 768)
						{
							cursor_pos.x = 768;
						}
					}
				} break;
				case SDLK_ESCAPE:
				{
					clear();
				} break;
			}
		} break;
	}
}

Tile* Tile_Editor::hovered_tile()
{
	Ivec tile_count = map->get_tile_count();
	Ivec index_to_replace((int)(cursor_pos.y/32),
						  (int)(cursor_pos.x/32) % tile_count.x);
	Tile* old_tile = map->get_tiles()[index_to_replace.x]
									 [index_to_replace.y];
	return old_tile;
}
