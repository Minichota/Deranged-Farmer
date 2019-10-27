#include "game.hpp"
#include "pause-menu.hpp"
#include "ui-text.hpp"
#include "ui-image.hpp"
#include "ui-slider.hpp"
#include "ui-button.hpp"
#include "ui-rect.hpp"
#include "interpolators.hpp"
#include "settings.hpp"

Pause_Menu::Pause_Menu(SDL_Renderer* renderer):
Game_State(renderer)
{
}

void quit()
{
	Game::toggle_pause();
	Game::set_state(0);
}

void Pause_Menu::init()
{
	elements =
	{
		new UI_Text(renderer, Ivec(400,200), Ivec(300,150), Fvec(1.0f,1.0f), "PAUSED", "res/graphics/font.ttf", SDL_Color{255,255,255,255}, FILL),
		new UI_Text(renderer, Ivec(400,500), Ivec(0,0), Fvec(1.0f,1.0f), "Press enter to continue", "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL),
		new UI_Button(renderer, Ivec(0,0), Ivec(0,0), Fvec(1.0f,1.0f), &quit),
		new UI_Text(renderer, Ivec(0,0), Ivec(0,0), Fvec(1.0f,1.0f), "Main Menu", "res/graphics/font.ttf", SDL_Color{255,255,255,255}, NORMAL),
		new UI_Rect(renderer, Ivec(0,0), Ivec(0,0), Fvec(2.0f,2.0f), SDL_Color{255,255,255,255},NORMAL),
		new UI_Image(renderer, Ivec(745,550), Ivec(50,50), Fvec(1.0f,1.0f), FILL, "res/graphics/volume.png"),
		new UI_Slider(renderer, Ivec(745,580), Ivec(100,10), Fvec(1.0f,1.0f), 0, 100, 100, SDL_Color{255,255,255,255}, SDL_Color{127,127,127,255})
	};
	elements[0]->set_origin(elements[0]->get_size()/2);
	elements[1]->set_origin(elements[1]->get_size()/2);
	elements[2]->set_size(elements[3]->get_size());
	elements[4]->set_size(elements[3]->get_size()/2);
	elements[5]->set_origin(elements[5]->get_size()/2);
	elements[6]->set_origin(elements[6]->get_size()/2);

	dynamic_cast<UI_Slider*>(elements[6])->set_bind(&Settings::volume);

	uchar_interpolaters.push_back(Interpolator<unsigned char>{&elements[1]->get_color().a,0,255,750,750});
}

void Pause_Menu::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
				case SDLK_RETURN:
				{
					Game::toggle_pause();
				}
			}
		}
	}
	for(size_t i = 0; i < elements.size(); i++)
	{
		Event_Handler* element = dynamic_cast<Event_Handler*>(elements[i]);
		if(element != nullptr)
		{
			element->handle_event(event);
		}
	}
}
