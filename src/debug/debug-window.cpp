#include <iostream>
#include <algorithm>
#include <cctype>

#include "debug-window.hpp"
#include "error.hpp"
#include "util.hpp"
#include "sized.hpp"

#define MAX_SCROLL 1600

Debug_Window::Debug_Window(SDL_Renderer* renderer):
Renderable(renderer),
entity_creator(renderer, nullptr),
text_input(renderer, Ivec(0,0), Ivec(100,100), Fvec(1.0f,1.0f), "res/graphics/font.ttf", SDL_Color{255,0,255,255}, NORMAL),
console(renderer, Fvec(0,400), Fvec(800,208), Fvec(1.0f,1.0f), "", "res/graphics/font.ttf", SDL_Color{255,255,255,255}, WRAPPED)
{
	this->inner_selection = -1;
	this->outer_selection = -1;
	this->pos = Ivec(600,0);
	scroll_pos = 0;
	entity_creator.active = false;

	font = TTF_OpenFont("res/graphics/font.ttf", 16);
	Error(!font, {"failed to load font", SDL_GetError()});
	console.set_font_size(18);
	text_input.set_font_size(12);
}

Debug_Window::~Debug_Window()
{
	TTF_CloseFont(font);
}

void Debug_Window::update()
{
	if(entity_creator.active)
	{
		entity_creator.update();
	}
	text_input.update();
	inner_rects.clear();
	outer_rects.clear();
	console.clear();
	rects.clear();

	for(size_t i = 0; i < logs.size(); i++)
	{
		if(!logs[i].get_active())
		{
			logs.erase(logs.begin() + i);
		}
		else
		{
			push_console(logs[i].get_text());
		}
	}
}

void Debug_Window::render()
{
	if(entity_creator.active)
	{
		entity_creator.render();
	}
	// background blending
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 127);
	SDL_Rect x = {pos.x,pos.y,200,608};
	SDL_RenderFillRect(renderer, &x);
	x = {0,400,800,208};
	SDL_RenderFillRect(renderer, &x);

	Ivec draw_pos = {this->pos.x, this->pos.y - scroll_pos};
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	// rendering of outer layer
	SDL_Surface* surface;
	for(size_t i = 0; i < to_render.size(); i++)
	{
		if(to_render[i].texture == nullptr)
		{
			surface = TTF_RenderText_Solid(font, to_render[i].name.c_str(), SDL_Color{255,255,255,255});
			to_render[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);
		}
		Ivec tex_size;
		SDL_QueryTexture(to_render[i].texture, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect size_rect =
		{
			draw_pos.x,
			draw_pos.y,
			tex_size.x,
			tex_size.y
		};
		outer_rects.push_back(size_rect);
		SDL_RenderCopy(renderer, to_render[i].texture, NULL, &size_rect);
		draw_pos.y += tex_size.y;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	if(rects_active)
	{
		for(SDL_Rect x : rects)
		{
			SDL_RenderDrawRect(renderer, &x);
		}
	}

	if(outer_selection >= 0)
	{
		// rendering of outline of outer text
		Ivec tex_size;
		SDL_QueryTexture(to_render[outer_selection].texture, NULL, NULL, &tex_size.x, &tex_size.y);
		SDL_Rect selected_outline = {pos.x, pos.y + (-scroll_pos + 19 * outer_selection), tex_size.x, tex_size.y};
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(renderer, &selected_outline);


		// rendering entity's outline
		Sized<float>* entity = to_render[outer_selection].address;
		if(entity != nullptr)
		{
			Ivec pos = entity->get_collision_pos();
			Ivec size = entity->get_collision_size();
			Ivec scale = entity->get_scale();
			SDL_Rect entity_outline =
			{
				(int)std::round(pos.x),
				(int)std::round(pos.y),
				(int)std::round(size.x * scale.x),
				(int)std::round(size.y * scale.y)
			};
			SDL_RenderDrawRect(renderer, &entity_outline);
		}
		if(inner_selection >= 0)
		{
			// rendering of inner selection mini-rectangle
			Ivec tex_size;
			SDL_Rect selected_box_2 = {pos.x + 50, pos.y + 19 * inner_selection, 5, 5};
			SDL_RenderDrawRect(renderer, &selected_box_2);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}
		draw_pos = pos;
		for(size_t i = 0; i < to_render[outer_selection].values.size(); i++)
		{
			Ivec tex_size;
			std::string x = std::to_string(*to_render[outer_selection].values[i]);
			remove_zeros(x);

			surface = TTF_RenderText_Solid(font, x.c_str(), SDL_Color{255,255,255,255});
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_QueryTexture(texture, NULL, NULL, &tex_size.x, &tex_size.y);
			SDL_Rect size_rect =
			{
				draw_pos.x + 50,
				draw_pos.y,
				tex_size.x,
				tex_size.y
			};
			inner_rects.push_back(size_rect);
			SDL_RenderCopy(renderer, texture, NULL, &size_rect);
			draw_pos.y += tex_size.y;
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surface);
		}
	}
	if(!text_input.get_string().empty())
	{
		Sized<float>* address = to_render[outer_selection].address;
		text_input.set_abs_pos(Fvec(address->get_pos().x + address->get_size().x/2,
									address->get_pos().y + address->get_size().y/2));
		text_input.set_origin(text_input.get_size()/2);
		text_input.render();
	}
	console.render();
	clear_render_settings(renderer);
}

void Debug_Window::clear()
{
	text_input.set_string("");
	outer_selection = -1;
	inner_selection = -1;
	for(size_t i = 0; i < to_render.size(); i++)
	{
		SDL_DestroyTexture(to_render[i].texture);
	}
	rects.clear();
	to_render.clear();
	active = false;
}

void Debug_Window::handle_event(const SDL_Event& event)
{
	if(entity_creator.active)
	{
		entity_creator.handle_event(event);
	}
	else
	{
		if(active)
		{
			switch(event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
				{
					Ivec mouse_position = Ivec(event.button.x, event.button.y);
					switch(event.button.button)
					{
						case SDL_BUTTON_LEFT:
						{
							select(mouse_position);
						} break;
					}
				} break;
				case SDL_MOUSEWHEEL:
				{
					if(event.wheel.y > 0)
					{
						// scroll up
						this->scroll_pos -= 30;
						if(scroll_pos < 0)
						{
							scroll_pos = 0;
						}
					}
					if(event.wheel.y < 0)
					{
						// scroll down
						this->scroll_pos += 30;
						if(scroll_pos > MAX_SCROLL)
						{
							scroll_pos = MAX_SCROLL;
						}
					}
				} break;
				case SDL_KEYDOWN:
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_DELETE:
						{
							if(outer_selection >= 0 && (size_t)outer_selection < to_render.size())
							{
								// checking all tiles
								std::vector<std::vector<Tile*>>& tiles = level->get_map().get_tiles();
								std::vector<Map_Entity*>& map_entities = level->get_map().get_map_entities();
								std::vector<Map_Entity*>::iterator map_entity = std::find_if(map_entities.begin(), map_entities.end(), [&](Map_Entity* x) -> bool {return x == to_render[outer_selection].address;});
								std::vector<Entity*>& entities = level->get_entities();
								std::vector<Entity*>::iterator entity = std::find_if(entities.begin(), entities.end(), [&](Entity* x) -> bool {return x == to_render[outer_selection].address;});
								size_t y_index = 0;
								for(size_t i = 0; i < tiles.size(); i++)
								{
									std::vector<Tile*>::iterator tile = std::find_if(tiles[i].begin(), tiles[i].end(), [&](Tile* x) -> bool {return x == to_render[outer_selection].address;});
									if(tile != tiles[i].end())
									{
										y_index = i;
										Map& map = level->get_map();
										Ivec tile_size = map.get_tile_size();
										Tile* old_tile = tiles[y_index][std::distance(tiles[y_index].begin(), tile)];

										tiles[y_index][std::distance(tiles[y_index].begin(), tile)] = new Tile(nullptr, Fvec(old_tile->get_pos().x * tile_size.x, old_tile->get_pos().y * tile_size.y), tile_size);

										to_render.erase(to_render.begin() + outer_selection);
										delete old_tile;
										goto end;
									}
								}
								// checking all map entities
								if(map_entity != map_entities.end())
								{
									map_entities.erase(map_entities.begin() + std::distance(map_entities.begin(), map_entity));
									to_render.erase(to_render.begin() + outer_selection);
									goto end;
								}
								// checking all normal entities
								if(entity != entities.end())
								{
									entities.erase(entities.begin() + std::distance(entities.begin(), entity));
									to_render.erase(to_render.begin() + outer_selection);
									goto end;
								}
								end:
								if((size_t)outer_selection >= to_render.size())
								{
									// prevention of segfault where outer_selection is greater than the size
									outer_selection--;
								}
							}
							if((size_t)outer_selection >= to_render.size())
							{
								outer_selection = -1;
							}
						} break;
						case SDLK_BACKSPACE:
						{
							text_input.handle_event(event);
						} break;
						case SDLK_F11:
						{
							rects_active = !rects_active;
						} break;
						case SDLK_RETURN:
						{
							if(text_input.get_string().size() > 0)
							{
								*to_render[outer_selection].values[inner_selection] = atof(text_input.get_string().c_str());
								set_string(*to_render[outer_selection].values[inner_selection]);
							}
						} break;
						case SDLK_j:
						{
							// down
							if(keys[SDL_SCANCODE_LCTRL])
							{
								outer_selection++;
								if((size_t)outer_selection > to_render.size() - 1)
								{
									outer_selection = 0;
								}
								inner_selection = -1;
								set_string("");
								handle_keyboard_scrolling();
							}
							else if(keys[SDL_SCANCODE_LSHIFT] && inner_selection >= 0)
							{
								set_string(--(*to_render[outer_selection].values[inner_selection]));
							}
							else if(outer_selection >= 0)
							{
								inner_selection++;
								if((size_t)inner_selection > to_render[outer_selection].values.size() - 1)
								{
									inner_selection = 0;
								}
								set_string(*to_render[outer_selection].values[inner_selection]);
							}
						} break;
						case SDLK_k:
						{
							// up
							if(keys[SDL_SCANCODE_LCTRL])
							{
								outer_selection--;
								if(outer_selection < 0)
								{
									outer_selection = to_render.size() - 1;
								}
								inner_selection = -1;
								set_string("");
								handle_keyboard_scrolling();
							}
							else if(keys[SDL_SCANCODE_LSHIFT] && inner_selection >= 0)
							{
								set_string(++(*to_render[outer_selection].values[inner_selection]));
							}
							else if(outer_selection >= 0)
							{
								inner_selection--;
								if(inner_selection < 0)
								{
									inner_selection = to_render[outer_selection].values.size() - 1;
								}
								set_string(*to_render[outer_selection].values[inner_selection]);
							}
						} break;
						case SDLK_n:
						{
							if(keys[SDL_SCANCODE_LCTRL])
							{
								entity_creator.active = true;
							}
						} break;
						case SDLK_ESCAPE:
						{
							clear();
						} break;
					}
				} break;
				case SDL_TEXTINPUT:
				{
					if((isdigit(event.text.text[0]) || event.text.text[0] == '.' || event.text.text[0] == '-') && inner_selection >= 0)
					{
						text_input.handle_event(event);
					}
				} break;
			}
		}
	}
}

void Debug_Window::push_render(Sized<float>* address, std::string name_repr, std::vector<float*> values)
{
	Debug_Element maybe{address, name_repr, values};
	if(!(std::find_if(to_render.begin(), to_render.end(), [&cr = maybe](const Debug_Element& cr2) -> bool {return cr2.address == cr.address;}) != to_render.end()))
	{
		to_render.push_back(Debug_Element{address, name_repr, values});
	}
}

void Debug_Window::push_console(std::string text)
{
	if(text.back() != '\n')
	{
		text.push_back(' ');
	}
	this->console.append_text(text);
}

void Debug_Window::push_console(float text)
{
	std::string str = std::to_string(std::round(text));
	remove_zeros(str);
	str.push_back(' ');
	this->console.append_text(str);
}

void Debug_Window::push_rect(Fvec pos, Fvec size)
{
	SDL_Rect maybe{(int)std::round(pos.x),
				   (int)std::round(pos.y),
				   (int)std::round(size.x),
				   (int)std::round(size.y)};
	rects.push_back(maybe);
}

void Debug_Window::push_log(std::vector<const char*> text, long long life_time)
{
	std::string x;
	for(const char* i : text)
	{
		x.append(i);
	}
	logs.push_back(Console_Log(x, life_time));
}

void Debug_Window::toggle()
{
	this->active = !this->active;
	if(!active)
	{
		clear();
	}
}

void Debug_Window::refresh()
{
	clear();
	this->active = true;
}

void Debug_Window::select(Ivec pos)
{
	// check if user clicked an entity
	for(size_t i = 0; i < to_render.size(); i++)
	{
		Ivec e_pos = to_render[i].address->get_collision_pos();
		Ivec e_bot_right = e_pos + to_render[i].address->get_collision_size();
		if(pos.x > e_pos.x && pos.x < e_bot_right.x &&
		   pos.y > e_pos.y && pos.y < e_bot_right.y)
		{
			// clicked the entity
			outer_selection = i;
			std::string x_pos = std::to_string(to_render[i].address->get_collision_pos().x);
			std::string y_pos = std::to_string(to_render[i].address->get_collision_pos().y);
			remove_zeros(x_pos);
			remove_zeros(y_pos);
			push_log({"clicked entity: @", x_pos.c_str(), ", ", y_pos.c_str()});
			handle_keyboard_scrolling();
			return;
		}
	}
	// if the user didn't click any entities, it selects based off of the outer/inner selections
	for(size_t i = 0; i < outer_rects.size(); i++)
	{
		if(pos.x > outer_rects[i].x &&
		   pos.y > outer_rects[i].y &&
		   pos.x < outer_rects[i].x + outer_rects[i].w &&
		   pos.y < outer_rects[i].y + outer_rects[i].h)
		{
			text_input.set_string("");
			inner_selection = -1;
			outer_selection = i;
			return;
		}
	}
	for(size_t i = 0; i < inner_rects.size(); i++)
	{
		if(pos.x > inner_rects[i].x &&
		   pos.y > inner_rects[i].y &&
		   pos.x < inner_rects[i].x + inner_rects[i].w &&
		   pos.y < inner_rects[i].y + inner_rects[i].h)
		{
			inner_selection = i;
			set_string(*to_render[outer_selection].values[inner_selection]);
			return;
		}
	}
	inner_selection = -1;
	outer_selection = -1;

	text_input.set_string("");
}

void Debug_Window::set_string(std::string input)
{
	remove_zeros(input);
	text_input.set_string(input);
}

void Debug_Window::set_string(float input)
{
	std::string str = std::to_string(input);
	remove_zeros(str);
	text_input.set_string(str);
}

void Debug_Window::handle_keyboard_scrolling()
{
	int rect_pos = pos.y + (-scroll_pos + 19 * outer_selection);
	if(rect_pos >= 608)
	{
		scroll_pos += rect_pos;
	}
	while(rect_pos < 0)
	{
		scroll_pos -= 19;
		rect_pos = pos.y + (-scroll_pos + 19 * outer_selection);
	}
}

void Debug_Window::set_level(Level* level)
{
	this->level = level;
	this->entity_creator.set_level(level);
}

void remove_zeros(std::string& input)
{
	char* c = &input.back();
	while(*c == '0')
	{
		input.pop_back();
		c--;
	}
	// remove decimal point
	if(*c == '.')
	{
		input.pop_back();
	}
}
