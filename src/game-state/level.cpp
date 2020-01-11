#include <iostream>
#include <cassert>

#include "level.hpp"
#include "game.hpp"
#include "ui-text.hpp"
#include "ui-health_bar.hpp"
#include "player.hpp"
#include "error.hpp"
#include "collisions.hpp"
#include "interpolators.hpp"
#include "io.hpp"
#include "bison.hpp"
#include "snake.hpp"

Level::Level(SDL_Renderer* renderer, const char* entity_file_path, const char* map_data_file_path, const char* map_image_file_path):
Game_State(renderer),
entity_file_path(entity_file_path),
map(renderer, map_data_file_path, map_image_file_path, Ivec(32,32)),
tile_editor(renderer),
map_data_file_path(map_data_file_path),
map_image_file_path(map_image_file_path)
{
	tile_editor.active = false;
}

Level::~Level()
{
	clear();
}

void Level::update()
{
	if(tile_editor.active)
	{
		tile_editor.update();
	}
	Game_State::update();
	map.update();
	for(Entity* entity : entities)
	{
		entity->update();
		map.handle_collision(entity);
		entity->move();
	}
	for(AI* ai : ais)
	{
		ai->update();
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
	for(Item* item : items)
	{
		item->render();
	}
	Game_State::render();
	if(tile_editor.active)
	{
		tile_editor.render();
	}
}

void Level::init()
{
	this->items =
	{
		new Item(renderer, this, Ivec(50, 50), "res/graphics/hoe.png")
	};
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
	tile_editor.set_map(&map);
}

void Level::clear()
{
	for(Entity* entity : entities)
	{
		delete entity;
	}
	entities.clear();
	for(AI* ai : ais)
	{
		delete ai;
	}
	ais.clear();
	map.clear();
	tile_editor.active = false;
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
				case SDLK_p:
				{
					Player* player = dynamic_cast<Player*>(entities[0]);
					for(size_t i = 0; i < items.size(); i++)
					{
						if(test_collision(player->get_pos(), player->get_size(),
										  items[i]->get_pos(), items[i]->get_size()))
						{
							player->get_inventory().pick_item(items[i]);
							items.erase(items.begin() + i);
						}
					}
				} break;
				case SDLK_ESCAPE:
				{
					if(!tile_editor.active)
					{
						Game::toggle_pause();
					}
				} break;
				case SDLK_e:
				{
					tile_editor.active = true;
				} break;
				case SDLK_F4:
				{
					save_level();
				} break;
			}
		}
	}
	for(Entity* entity : entities)
	{
		entity->handle_event(event);
	}
	if(tile_editor.active)
	{
		tile_editor.handle_event(event);
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
				Bison* bison = new Bison(renderer, Fvec(properties[i][0], properties[i][1]), Fvec(properties[i][2], properties[i][3]));
				bison->load_texture("res/graphics/bison.png");
				AI_Roaming* bison_ai = new AI_Roaming(this->map, bison, 3000);
				ais.push_back(bison_ai);
				entities.push_back(bison);
				delete types[i];
			} break;
			case 1:
			{
				Snake* snake = new Snake(renderer, Fvec(properties[i][0], properties[i][1]), Fvec(properties[i][2], properties[i][3]));
				snake->load_texture("res/graphics/snake.png");
				AI_Roaming* snake_ai = new AI_Roaming(this->map, snake, 3000);
				ais.push_back(snake_ai);
				entities.push_back(snake);
				delete types[i];
			} break;
		}
	}
	types.clear();
}

void Level::save_level()
{
	// construct data
	std::string data;
	data.reserve(4000);
	// sizing
	Ivec map_size = map.get_tile_count();
	data.append("width=");
	data.append(std::to_string(map_size.x));
	data.push_back('\n');
	data.append("height=");
	data.append(std::to_string(map_size.y));
	data.push_back('\n');
	// level tile_data
	std::vector<std::vector<Tile*>>& tiles = map.get_tiles();
	for(size_t i = 0; i < tiles.size(); i++)
	{
		for(size_t j = 0; j < tiles[i].size(); j++)
		{
			if(j != 0)
			{
				data.push_back(',');
			}
			if(tiles[i][j]->is_null())
			{
				data.push_back('0');
			}
			else
			{
				// find tile_pos
				Ivec full_size;
				Ivec tile_pos = tiles[i][j]->get_relative_pos()/32;
				SDL_QueryTexture(full_texture, NULL, NULL, &full_size.x, &full_size.y);
				full_size = full_size / 32;
				data.append(std::to_string(tile_pos.y * full_size.y + tile_pos.x + 1));
			}
		}
		data.push_back('\n');
	}

	// level map_data
	std::vector<Map_Entity*>& map_entities = map.get_map_entities();
	for(Map_Entity* e : map_entities)
	{
		if((int)e->get_rotation() % 90 != 0)
		{
			Game::debug->push_log({"failed to save, an entity has the rotation of: ",  std::to_string((int)e->get_rotation()).c_str()});
			return;
		}
		data.append("type=");
		data.append(std::to_string(e->get_type()));
		data.push_back('\n');
		std::string e_data;
		e_data.append(std::to_string((int)e->get_pos().x));
		e_data.push_back(',');
		e_data.append(std::to_string((int)e->get_pos().y));
		e_data.push_back(',');
		e_data.append(std::to_string((int)e->get_size().x));
		e_data.push_back(',');
		e_data.append(std::to_string((int)e->get_size().y));
		e_data.push_back(',');
		e_data.append(std::to_string((int)e->get_rotation()));
		e_data.push_back('\n');
		data.append(e_data);
	}

	// write data
	write(map_data_file_path.c_str(), data);
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
