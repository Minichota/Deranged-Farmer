#include <iostream>
#include <cassert>

#include "level.hpp"
#include "game.hpp"
#include "ui-text.hpp"
#include "ui-health_bar.hpp"
#include "player.hpp"
#include "error.hpp"
#include "collisions.hpp"
#include "io.hpp"
#include "bison.hpp"

Level::Level(SDL_Renderer* renderer, const char* entity_file_path, const char* map_data_file_path, const char* map_image_file_path):
Game_State(renderer),
entity_file_path(entity_file_path),
map(renderer, map_data_file_path, map_image_file_path, Ivec(32,32)),
map_data_file_path(map_data_file_path),
map_image_file_path(map_image_file_path)
{
}

Level::~Level()
{
	clear();
}

void Level::update()
{
	Game_State::update();
	map.update();
	for(Entity* entity : entities)
	{
		entity->update();
		map.handle_collision(entity);
		entity->move();
	}
	handle_entity_collision(entities[0], entities[1]);
}

void Level::render()
{
	SDL_RenderCopy(renderer, background, NULL, NULL);
	map.render();
	for(Entity* entity : entities)
	{
		entity->render();
	}
	Game_State::render();
}

void Level::init()
{
	entities =
	{
		new Player(renderer, Ivec(50,50), Ivec(27,27))
	};
	UI_Health_Bar* health_Bar = new UI_Health_Bar(renderer, Ivec(400,0), Ivec(350/3.0f,50/3.0f), Fvec(3.0f,3.0f), SDL_Color{255, 0, 0, 255}, SDL_Color{255,100,0,255}, &entities[0]->get_health(), entities[0]->get_max_health());
	health_Bar->set_origin(Ivec(health_Bar->get_size().x/2,0));
	elements =
	{
		health_Bar
	};
	SDL_Texture* player_texture;
	{
		player_texture = IMG_LoadTexture(renderer, "res/graphics/player_test.png");
		Error(player_texture == nullptr, {"Failed to load player texture", SDL_GetError()});
	}
	{
		background = IMG_LoadTexture(renderer, "res/graphics/background.png");
		Error(!background, {"Failed to load background", SDL_GetError()});
	}
	entities[0]->set_texture(player_texture);
	load_entities();
	map.init();
}

void Level::clear()
{
	for(Entity* entity : entities)
	{
		delete entity;
	}
	entities.clear();
	map.clear();
	Game_State::clear();
	SDL_DestroyTexture(background);
}

void Level::handle_event(const SDL_Event& event)
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

void Level::load_entities()
{
	std::string data = read(entity_file_path.c_str());
	std::vector<Settings::Data<int>*> types;
	std::vector<std::vector<int>> properties;

	parse(data, '=', types);
	parse_csv(data, properties);

	assert(types.size() == properties.size());

	for(size_t i = 0; i < properties.size(); i++)
	{
		switch(types[i]->data)
		{
			case 0:
			{
				// some weird entity
				// TODO implement some entity classes
				Bison* bison = new Bison(renderer, Fvec(properties[i][0], properties[i][1]), Fvec(properties[i][2], properties[i][3]));
				bison->load_texture("res/graphics/bison.png");
				entities.push_back(bison);
				delete types[i];
			} break;
		}
	}
	types.clear();
}

void Level::handle_entity_collision(Entity* e_1, Entity* e_2)
{
	if(test_collision(e_1->get_collision_pos(), e_1->get_collision_size(),
					  e_2->get_collision_pos(), e_2->get_collision_size()))
	{
		// player collided with some shite
	}
}

Map& Level::get_map()
{
	return this->map;
}

void Level::push_entity(Entity* entity)
{
	this->entities.push_back(entity);
}

std::vector<Entity*>& Level::get_entities()
{
	return this->entities;
}
