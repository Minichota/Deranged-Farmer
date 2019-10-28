#include <iostream>

#include "level.hpp"
#include "game.hpp"
#include "ui-text.hpp"
#include "ui-health_bar.hpp"
#include "player.hpp"
#include "error.hpp"

Level::Level(SDL_Renderer* renderer, const char* entity_file_path, const char* map_file_path):
Game_State(renderer),
entity_file_path(entity_file_path),
map_file_path(map_file_path)
{
}

Level::~Level()
{
	clear();
}

void Level::update()
{
	Game_State::update();
	for(Entity* entity : entities)
	{
		entity->update();
	}
}

void Level::render()
{
	Game_State::render();
	for(Entity* entity : entities)
	{
		entity->render();
	}
}

void Level::init()
{
	entities =
	{
		new Player(renderer, Ivec(400,300), Ivec(32,32), Fvec(1.0f,1.0f), Ivec(16,16))
	};
	UI_Health_Bar* health_Bar = new UI_Health_Bar(renderer, Ivec(400,0), Ivec(350/3.0f,50/3.0f), Fvec(3.0f,3.0f), SDL_Color{255, 0, 0, 255}, SDL_Color{255,100,0,255}, &entities[0]->get_health(), entities[0]->get_max_health());
	health_Bar->set_origin(Ivec(health_Bar->get_size().x/2,0));
	elements =
	{
		health_Bar
	};
	SDL_Texture* player_texture;
	{
		player_texture = IMG_LoadTexture(renderer, "res/graphics/player.png");
		Error(player_texture == nullptr, {"Failed to load player texture", SDL_GetError()});
	}
	entities[0]->set_texture(player_texture);
}

void Level::clear()
{
	for(Entity* entity : entities)
	{
		delete entity;
	}
	entities.clear();

	Game_State::clear();
}

void Level::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				{
					Game::toggle_pause();
				} break;
			}
		}
	}
	for(Entity* entity : entities)
	{
		entity->handle_event(event);
	}
}
