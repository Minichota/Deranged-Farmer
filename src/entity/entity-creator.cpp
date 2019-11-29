#include "entity-creator.hpp"
#include "game.hpp"
#include "util.hpp"
#include "tile.hpp"
#include "map-entity.hpp"
#include "bison.hpp"
#include "util.hpp"

Entity_Creator::Entity_Creator(SDL_Renderer* const renderer, Level* level):
Renderable(renderer)
{
	selected_name = 0;
	selected_field = 0;
	curr_state = 0;
	names =
	{
		{ "Tile",  {"x: ", "y: ", "w: ", "h: ", "type: "}},
		{ "Fence", {"x: ", "y: ", "w: ", "h: ", "rotation: "}},
		{ "Bison", {"x: ", "y: ", "w: ", "h: "}}
	};
	for(size_t i = 0; i < names.size(); i++)
	{
		entity_names.push_back(new UI_Text(renderer, Ivec(0, 18*i), Ivec(0,0), Fvec(1.0f, 1.0f), names[i].name, "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL));
		entity_names[i]->set_font_size(15);
	}
}

Entity_Creator::~Entity_Creator()
{
}

void Entity_Creator::update()
{
	for(UI_Text* x : entity_names)
	{
		x->update();
	}
	if(curr_state)
	{
		inputs[selected_field]->update();
	}
}

void Entity_Creator::render()
{
	SDL_Rect shadow =
	{
		0,
		0,
		120,
		608
	};
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(renderer, &shadow);

	for(UI_Text* x : entity_names)
	{
		x->render();
	}

	if(curr_state)
	{
		std::string copy = inputs[selected_field]->get_string();
		inputs[selected_field]->set_string(names[selected_name].input_repr[selected_field] + copy);
		inputs[selected_field]->render();
		inputs[selected_field]->set_string(copy);
	}

	Ivec outline_pos = entity_names[selected_name]->get_pos();
	Ivec outline_size = entity_names[selected_name]->get_size();
	SDL_Rect outline_box =
	{
		outline_pos.x,
		outline_pos.y,
		outline_size.x,
		outline_size.y
	};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(renderer, &outline_box);
	clear_render_settings(renderer);
}

void Entity_Creator::handle_event(const SDL_Event& event)
{
	if(curr_state)
	{
		inputs[selected_field]->handle_event(event);
	}
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_n:
				{
					selected_name = 0;
					selected_field = 0;
					curr_state = 0;
					for(UI_Text_Input* x : inputs)
					{
						delete x;
					}
					inputs.clear();
					this->active = false;
				} break;
				case SDLK_j:
				{
					if(keys[SDL_SCANCODE_LCTRL])
					{
						if(curr_state == 0)
						{
							if(inputs[selected_name]->get_string() == "")
							{
								// check if previous input is null
								inputs[selected_name]->get_string() = "0";
							}
							selected_name++;
							if((size_t)selected_name > entity_names.size() - 1)
							{
								selected_name = 0;
							}
						}
						else
						{
							selected_field++;
							if((size_t)selected_field > names[selected_name].input_repr.size() - 1)
							{
								selected_field = 0;
							}
						}
					}
				} break;
				case SDLK_k:
				{
					if(keys[SDL_SCANCODE_LCTRL])
					{
						if(curr_state == 0)
						{
							if(inputs[selected_name]->get_string() == "")
							{
								// check if previous input is null
								inputs[selected_name]->get_string() = "0";
							}
							selected_name--;
							if(selected_name < 0)
							{
								selected_name = entity_names.size() - 1;
							}
						}
						else
						{
							selected_field--;
							if(selected_field < 0)
							{
								selected_field = names[selected_name].input_repr.size() - 1;
							}
						}
					}
				} break;
				case SDLK_RETURN:
				{
					if(curr_state == 0)
					{
						for(size_t i = 0; i < names[selected_name].input_repr.size(); i++)
						{
							inputs.push_back(new UI_Text_Input(renderer, Ivec(400,30), Ivec(0,0), Fvec(1.0f,1.0f), "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL));
							inputs[i]->set_string("0");
						}
						curr_state++;
					}
					else
					{
						curr_state = 0;
						if(inputs[selected_name]->get_string() == "")
						{
							// check if current input is null
							inputs[selected_name]->get_string() = "0";
						}
						switch(selected_name)
						{
							case 0:
							{
								Tile* tile = new Tile(renderer, Fvec(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string())),
																Fvec(std::stof(inputs[2]->get_string()), std::stof(inputs[3]->get_string())));
								switch(std::stoi(inputs[4]->get_string()))
								{
									case 0:
									{
										tile->load_texture("res/graphics/tile_map.png", Ivec(0,0));
										level->get_map().push_tile(tile);
									} break;
									case 1:
									{
										tile->load_texture("res/graphics/tile_map.png", Ivec(32,0));
										level->get_map().push_tile(tile);
									} break;
									default:
									{
										Game::debug->push_log({"That type of tile: ", inputs[4]->get_string().c_str(), " does not exist"});
										delete tile;
									} break;
								}
							} break;
							case 1:
							{
								if(std::stoi(inputs[4]->get_string()) % 90 != 0)
								{
									Game::debug->push_log({"rotation must be divisible by 90"});
								}
								if(std::stoi(inputs[4]->get_string()) % 90 == 0)
								{
									Map_Entity* fence = new Map_Entity(renderer, Fvec(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string())),
																				 Fvec(std::stof(inputs[2]->get_string()), std::stof(inputs[3]->get_string())),
																				 std::stof(inputs[4]->get_string()));
									if(fence->get_size().x <= 0 || fence->get_size().y <= 0)
									{
										Game::debug->push_log({"width or height cannot be <= 0"});
									}
									if(fence->get_size().x > 0 && fence->get_size().y > 0)
									{
										fence->load_texture("res/graphics/fence.png");
										level->get_map().push_entity(fence);
									}
									else
									{
										delete fence;
									}
								}
							} break;
							case 2:
							{
								Bison* bison = new Bison(renderer, Fvec(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string())),
																   Fvec(std::stof(inputs[2]->get_string()), std::stof(inputs[3]->get_string())));
								if(bison->get_size().x <= 0 || bison->get_size().y <= 0)
								{
									Game::debug->push_log({"width or height cannot be <= 0"});
								}
								if(bison->get_size().x > 0 && bison->get_size().y > 0)
								{
									bison->load_texture("res/graphics/bison.png");
									level->push_entity(bison);
								}
								else
								{
									delete bison;
								}
							} break;
						}
						selected_name = 0;
						selected_field = 0;
						active = false;
						for(UI_Text_Input* x : inputs)
						{
							delete x;
						}
						inputs.clear();
					}
				} break;
			}
		} break;
	}
}

void Entity_Creator::set_level(Level* level)
{
	this->level = level;
}
