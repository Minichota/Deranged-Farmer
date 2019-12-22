#include "entity-creator.hpp"
#include "game.hpp"
#include "util.hpp"
#include "tile.hpp"
#include "map-entity.hpp"
#include "bison.hpp"
#include "snake.hpp"
#include "util.hpp"

Entity_Creator::Entity_Creator(SDL_Renderer* const renderer, Level* level):
Renderable(renderer)
{
	selected_name = 0;
	selected_field = 0;
	curr_state = 0;
	names =
	{
		{ "Tile",  {"x: ", "y: ", "type: "}, Fvec(32,32), false},
		{ "Fence", {"x: ", "y: ", "rotation: "}, Fvec(30,4), true},
		{ "Bison", {"x: ", "y: "}, Fvec(24, 16), false},
		{ "Snake", {"x: ", "y: "}, Fvec(28, 14), false}
	};
	for(size_t i = 0; i < names.size(); i++)
	{
		entity_names.push_back(new UI_Text(renderer, Ivec(400, 150 + 18*i), Ivec(0,0), Fvec(1.0f, 1.0f), names[i].name, "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL));
		entity_names[i]->set_font_size(15);
		entity_names[i]->set_origin(Fvec(entity_names[i]->get_size().x/2, 0));
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
	if(curr_state == 0)
	{
		const SDL_Rect shadow =
		{ 350, 150, 100, (int)entity_names.size() * 18 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
		SDL_RenderFillRect(renderer, &shadow);

		for(size_t i = 0; i < entity_names.size(); i++)
		{
			// a slow approach but changes size and color
			if((int)i == selected_name)
			{
				entity_names[i]->set_color(SDL_Color{255,127,0,255}, false);
			}
			else
			{
				entity_names[i]->set_color(SDL_Color{255,255,255,255}, false);
			}
			entity_names[i]->reload_texture();
			entity_names[i]->set_origin(Fvec(entity_names[i]->get_size().x/2, 0));
			entity_names[i]->render();
		}
	}

	if(curr_state)
	{

		for(size_t i = 0; i < inputs.size(); i++)
		{
			// a slow approach but changes size and color
			if((int)i == selected_field)
			{
				inputs[i]->get_text().set_color(SDL_Color{0,0,255,255});
			}
			else
			{
				inputs[i]->get_text().set_color(SDL_Color{255,255,255,255});
			}
			std::string copy = inputs[i]->get_string();
			inputs[i]->set_string(names[selected_name].input_repr[i] + copy);
			inputs[i]->render();
			inputs[i]->set_string(copy);
		}

		// drawing outline for where entity will be
		if(!inputs[selected_field]->get_string().empty())
		{
			Ivec curr_pos  = Ivec(std::stoi(inputs[0]->get_string()), std::stoi(inputs[1]->get_string()));
			Ivec curr_size = names[selected_name].size;
			Sized<int> x;
			if(names[selected_name].rotateable && std::stoi(inputs[2]->get_string()) % 90 == 0)
			{
				// has rotation?
				x = Sized<int>(curr_pos, curr_size, Fvec(1.0f,1.0f), std::stoi(inputs[2]->get_string()));
			}
			else
			{
				x = Sized<int>(curr_pos, curr_size, Fvec(1.0f,1.0f));
			}
			SDL_Rect entity_pos =
			{
				x.get_collision_pos().x,
				x.get_collision_pos().y,
				x.get_collision_size().x,
				x.get_collision_size().y
			};
			SDL_RenderDrawRect(renderer, &entity_pos);
		}
	}
	clear_render_settings(renderer);
}

void Entity_Creator::clear()
{
	curr_state = 0;
	selected_name = 0;
	selected_field = 0;
	for(UI_Text_Input* x : inputs)
	{
		delete x;
	}
	inputs.clear();
}

void Entity_Creator::handle_event(const SDL_Event& event)
{
	switch(event.type)
	{
		case SDL_TEXTINPUT:
		{
			if(curr_state)
			{
				if((isdigit(event.text.text[0]) || event.text.text[0] == '.' || event.text.text[0] == '-'))
				{
					inputs[selected_field]->handle_event(event);
				}
			}
		} break;
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_n:
				{
					clear();
				} break;
				case SDLK_j:
				{
					if(keys[SDL_SCANCODE_LSHIFT])
					{
						if(curr_state != 0)
						{
							std::string& input_string = inputs[selected_field]->get_string();
							if(input_string.empty())
							{
								input_string = "0";
							}
							if(selected_field < 2 && selected_name == 0)
							{
								input_string = std::to_string(std::stof(input_string) - 32.0f);
							}
							else
							{
								input_string = std::to_string(std::stof(input_string) - 1.0f);
							}
							remove_zeros(input_string);
						}
					}
					else if(keys[SDL_SCANCODE_LCTRL])
					{
						if(curr_state == 0)
						{
							selected_name++;
							if((size_t)selected_name > entity_names.size() - 1)
							{
								selected_name = 0;
							}
						}
						else
						{
							if(inputs[selected_field]->get_string() == "")
							{
								// check if previous input is null
								inputs[selected_field]->get_string() = "0";
							}
							selected_field++;
							if((size_t)selected_field > names[selected_name].input_repr.size() - 1)
							{
								selected_field = 0;
							}
						}
					}
					else
					{
						if(curr_state == 0)
						{
							selected_name++;
							if((size_t)selected_name > entity_names.size() - 1)
							{
								selected_name = 0;
							}
						}
						else
						{
							if(inputs[1]->get_string() == "")
							{
								// check if previous input is null
								inputs[1]->get_string() = "0";
							}
							if(selected_name == 0)
							{
								inputs[1]->get_string() = std::to_string(std::stoi(inputs[1]->get_string()) + 32);
							}
							else
							{
								inputs[1]->get_string() = std::to_string(std::stoi(inputs[1]->get_string()) + 1);
							}
						}
					}
				} break;
				case SDLK_k:
				{
					if(keys[SDL_SCANCODE_LSHIFT])
					{
						if(curr_state != 0)
						{
							std::string& input_string = inputs[selected_field]->get_string();
							if(input_string.empty())
							{
								input_string = "0";
							}
							if(selected_field < 2 && selected_name == 0)
							{
								input_string = std::to_string(std::stof(input_string) + 32.0f);
							}
							else
							{
								input_string = std::to_string(std::stof(input_string) + 1.0f);
							}
							remove_zeros(input_string);
						}
					}
					else if(keys[SDL_SCANCODE_LCTRL])
					{
						if(curr_state == 0)
						{
							selected_name--;
							if(selected_name < 0)
							{
								selected_name = entity_names.size() - 1;
							}
						}
						else
						{
							if(inputs[selected_field]->get_string() == "")
							{
								// check if previous input is null
								inputs[selected_field]->get_string() = "0";
							}
							selected_field--;
							if(selected_field < 0)
							{
								selected_field = names[selected_name].input_repr.size() - 1;
							}
						}
					}
					else
					{
						if(curr_state == 0)
						{
							selected_name--;
							if(selected_name < 0)
							{
								selected_name = entity_names.size() - 1;
							}
						}
						else
						{
							if(inputs[1]->get_string() == "")
							{
								// check if previous input is null
								inputs[1]->get_string() = "0";
							}
							if(selected_name == 0)
							{
								inputs[1]->get_string() = std::to_string(std::stoi(inputs[1]->get_string()) - 32);
							}
							else
							{
								inputs[1]->get_string() = std::to_string(std::stoi(inputs[1]->get_string()) - 1);
							}
						}
					}
				} break;
				case SDLK_h:
				{
					if(curr_state == 1)
					{
						if(inputs[0]->get_string() == "")
						{
							// check if previous input is null
							inputs[0]->get_string() = "0";
						}
						if(selected_name == 0)
						{
							inputs[0]->get_string() = std::to_string(std::stoi(inputs[0]->get_string()) - 32);
						}
						else
						{
							inputs[0]->get_string() = std::to_string(std::stoi(inputs[0]->get_string()) - 1);
						}
					}
				} break;
				case SDLK_l:
				{
					if(curr_state == 1)
					{
						if(inputs[0]->get_string() == "")
						{
							// check if previous input is null
							inputs[0]->get_string() = "0";
						}
						if(selected_name == 0)
						{
							inputs[0]->get_string() = std::to_string(std::stoi(inputs[0]->get_string()) + 32);
						}
						else
						{
							inputs[0]->get_string() = std::to_string(std::stoi(inputs[0]->get_string()) + 1);
						}
					}
				} break;
				case SDLK_RETURN:
				{
					if(curr_state == 0)
					{
						for(size_t i = 0; i < names[selected_name].input_repr.size(); i++)
						{
							inputs.push_back(new UI_Text_Input(renderer, Ivec(6,i * 20), Ivec(0,0), Fvec(1.0f,1.0f), "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL));
							inputs[i]->set_string("0");
							inputs[i]->set_font_size(24);
						}
						curr_state++;
					}
					else
					{
						//curr_state = 0;
						if(inputs[selected_field]->get_string() == "")
						{
							// check if current input is null
							inputs[selected_field]->get_string() = "0";
						}
						switch(selected_name)
						{
							case 0:
							{
								Fvec pos(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string()));
								Ivec tile_count = level->get_map().get_tile_count();
								Ivec index_to_replace((int)(pos.y/32),
													  (int)(pos.x/32) % tile_count.x);
								if(std::stoi(inputs[0]->get_string()) % 32 != 0 || std::stoi(inputs[1]->get_string()) % 32 != 0)
								{
									Game::debug->push_log({"x and y must `mod 32` to 0", "\n"});
									break;
								}
								if(std::stoi(inputs[0]->get_string()) < 0 || std::stoi(inputs[1]->get_string()) < 0 ||
								  (std::stoi(inputs[0]->get_string()) > 768 || std::stoi(inputs[1]->get_string()) > 576))
								{
									Game::debug->push_log({"Tile must be within map", "\n"});
									break;
								}

								if(std::stoi(inputs[2]->get_string()) < 3)
								{
									Tile* old_tile = level->get_map().get_tiles()[index_to_replace.x]
																				 [index_to_replace.y];
									old_tile->set_relative_pos(Ivec(std::stoi(inputs[2]->get_string())%tile_count.y * level->get_map().get_tile_size().x,
															   	   (std::stoi(inputs[2]->get_string())/tile_count.x * level->get_map().get_tile_size().y)));
									if(old_tile->is_null())
									{
										old_tile->set_renderer(renderer);
									}
									Game::debug->refresh();
								}
								else
								{
									Game::debug->push_log({"That type of tile: ", inputs[2]->get_string().c_str(), " does not exist", "\n"});
								}
							} break;
							case 1:
							{
								if(std::stoi(inputs[2]->get_string()) % 90 == 0)
								{
									Map_Entity* fence = new Map_Entity(renderer, Fvec(std::stof(inputs[0]->get_string()),
																					  std::stof(inputs[1]->get_string())),
																					  names[selected_name].size,
																				 	  std::stof(inputs[2]->get_string()));
									fence->load_texture("res/graphics/fence.png");
									level->get_map().push_entity(fence);
								}
								else
								{
									Game::debug->push_log({"rotation must be divisible by 90", "\n"});
								}
							} break;
							case 2:
							{
								Bison* bison = new Bison(renderer, Fvec(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string())),
																   names[selected_name].size);
								bison->load_texture("res/graphics/bison.png");
								level->push_entity(bison);
							} break;
							case 3:
							{
								Snake* snake = new Snake(renderer, Fvec(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string())),
																   names[selected_name].size);
								snake->load_texture("res/graphics/snake.png");
								level->push_entity(snake);
							} break;
						}
					}
				} break;
				case SDLK_DELETE:
				{
					if(curr_state == 1)
					{
						if(names[selected_name].name == "Tile")
						{
							if(std::stoi(inputs[0]->get_string()) % 32 != 0 || std::stoi(inputs[1]->get_string()) % 32 != 0)
							{
								Game::debug->push_log({"x and y must `mod 32` to 0", "\n"});
								break;
							}
							if(std::stoi(inputs[0]->get_string()) < 0 || std::stoi(inputs[1]->get_string()) < 0 ||
							  (std::stoi(inputs[0]->get_string()) > 768 || std::stoi(inputs[1]->get_string()) > 576))
							{
								Game::debug->push_log({"Tile must be within map", "\n"});
								break;
							}
							Fvec pos(std::stof(inputs[0]->get_string()), std::stof(inputs[1]->get_string()));
							Ivec tile_count = level->get_map().get_tile_count();
							Ivec index_to_replace((int)(pos.y/32),
												  (int)(pos.x/32) % tile_count.x);
							Tile* old_tile = level->get_map().get_tiles()[index_to_replace.x]
																		 [index_to_replace.y];
							old_tile->set_renderer(nullptr);

						}
					}
				} break;
				case SDLK_BACKSPACE:
				{
					inputs[selected_field]->handle_event(event);
				} break;
				case SDLK_ESCAPE:
				{
					if(curr_state == 0)
					{
						clear();
						active = false;
					}
					else
					{
						for(UI_Text_Input* x : inputs)
						{
							delete x;
						}
						inputs.clear();
						curr_state--;
					}
				}
			}
		} break;
	}
}

void Entity_Creator::set_level(Level* level)
{
	this->level = level;
}
