#include "item.hpp"
#include "level.hpp"

#define delay 200
Item::Item(SDL_Renderer* renderer, Level* level, Sized<float>* parent, Ivec pos,
		   std::string icon_path, std::string animation_path) :
Renderable(renderer),
Sized(pos, Fvec(32, 32), Fvec(1.0f, 1.0f))
{
	this->level = level;
	this->pos_2 = pos;
	{
		this->texture = IMG_LoadTexture(renderer, icon_path.c_str());
		Error(this->texture == nullptr,
			  { "Failed to load texture: ", icon_path.c_str() });
	}
	this->animation =
		new Animation(renderer, this, animation_path, Ivec(16, 16), delay);
	this->animation->init();
	this->start_time = 0;
	this->parent = parent;
}

Item::~Item()
{
	SDL_DestroyTexture(this->texture);
}

void Item::update()
{
}

void Item::render()
{
	SDL_Rect src{ 0, 0, 32, 32 };
	SDL_Rect dst{ (int)std::round(pos_2.x), (int)std::round(pos_2.y),
				  (int)std::round(size.x), (int)std::round(size.y) };
	SDL_RenderCopy(renderer, texture, &src, &dst);
	if(SDL_GetTicks() - start_time > delay && swinging)
	{
		swinging = false;
	}
	if(swinging)
	{
		this->scale = Fvec(2.0f, 2.0f);
		this->pos = parent->get_pos() / scale + parent->get_size() / 2 / scale -
					Ivec(8, 8) + offset;
		animation->render();
	}
}

void Item::use(const Vim_Key key)
{
	switch(key)
	{
		case H:
		{
			if(SDL_GetTicks() - animation->get_delay() + start_time > delay &&
			   !swinging)
			{
				start_time = SDL_GetTicks();
				swinging = true;
				offset = Ivec(-8, 0);
				this->rotation = 180;
			}
		}
		break;
		case J:
		{
			if(SDL_GetTicks() - animation->get_delay() + start_time > delay &&
			   !swinging)
			{
				start_time = SDL_GetTicks();
				swinging = true;
				offset = Ivec(0, 8);
				this->rotation = 90;
			}
		}
		break;
		case K:
		{
			if(SDL_GetTicks() - animation->get_delay() + start_time > delay &&
			   !swinging)
			{
				start_time = SDL_GetTicks();
				swinging = true;
				offset = Ivec(0, -8);
				this->rotation = 270;
			}
		}
		break;
		case L:
		{
			if(SDL_GetTicks() - animation->get_delay() + start_time > delay &&
			   !swinging)
			{
				start_time = SDL_GetTicks();
				swinging = true;
				offset = Ivec(8, 0);
				this->rotation = 0;
			}
		}
		break;
	}
}

void Item::pick()
{
	dropped = false;
}

void Item::set_e_pos(Ivec pos)
{
	this->pos_2 = pos;
}
