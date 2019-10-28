#include <iostream>

#include "level.hpp"
#include "game.hpp"
#include "ui-text.hpp"
#include "player.hpp"

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
	UI_Text* thing = new UI_Text(renderer, Ivec(400,300), Ivec(100,50), Fvec(0.0f,0.0f), "This is the level!", "res/graphics/font.ttf", SDL_Color{255,255,255,255}, FILL);
	thing->set_origin(thing->get_size()/2);
	elements =
	{
		thing
	};
	entities =
	{
		new Player(renderer, Ivec(400,300), Ivec(32,32), Fvec(1.0f,1.0f), Ivec(16,16))
	};
	SDL_Texture* player_texture = IMG_LoadTexture(renderer, "res/graphics/player.png");
	if(player_texture == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
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
				}
			}
		}
	}
	for(Entity* entity : entities)
	{
		entity->handle_event(event);
	}
}
