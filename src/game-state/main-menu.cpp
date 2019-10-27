#include <iostream>

#include "main-menu.hpp"
#include "ui-base.hpp"
#include "ui-text.hpp"
#include "ui-button.hpp"
#include "ui-slider.hpp"
#include "ui-switch.hpp"
#include "ui-text-input.hpp"
#include "ui-rect.hpp"
#include "ui-image.hpp"
#include "interpolators.hpp"
#include "game.hpp"
#include "settings.hpp"

Main_Menu::Main_Menu(SDL_Renderer* renderer):
Game_State(renderer)
{
}

void test()
{
	Game::increment_state();
}

void Main_Menu::init()
{
	elements = {
		new UI_Rect(renderer, Ivec(400,100), Ivec(100, 100), Fvec(2.0f,1.5f), SDL_Color{255,0,255,255}, NORMAL),
		new UI_Text(renderer, Ivec(400,100), Ivec(0,0), Fvec(2.0f,1.5f), "Deranged farmer", "res/graphics/font.ttf", SDL_Color{0,255,255,255}, NORMAL),
		new UI_Button(renderer, Ivec(400,300), Ivec(40,20), Fvec(5.0f,5.0f), &test, SDL_Color{255,0,0,255}),
		new UI_Text(renderer, Ivec(400,300), Ivec(192,100), Fvec(1.0f,1.0f), "Start", "res/graphics/font.ttf", SDL_Color{255,255,255,255}, FILL),
		new UI_Image(renderer, Ivec(745,550), Ivec(50,50), Fvec(1.0f,1.0f), FILL, "res/graphics/volume.png"),
		new UI_Slider(renderer, Ivec(745,580), Ivec(100,10), Fvec(1.0f,1.0f), 0, 100, 100, SDL_Color{255,255,255,255}, SDL_Color{127,127,127,255})
	};

	dynamic_cast<UI_Text*>(elements[1])->set_font_size(30);
	dynamic_cast<UI_Slider*>(elements[5])->set_bind(&Settings::volume);

	elements[0]->set_size(elements[1]->get_size());

	elements[0]->set_origin(elements[0]->get_size()/2.0f);
	elements[1]->set_origin(elements[1]->get_size()/2.0f);
	elements[2]->set_origin(elements[2]->get_size()/2.0f);
	elements[3]->set_origin(elements[3]->get_size()/2.0f);
	elements[4]->set_origin(elements[4]->get_size()/2.0f);
	elements[5]->set_origin(elements[5]->get_size()/2.0f);

	float_interpolaters.push_back(Interpolator<float>{&elements[1]->get_scale().x, 1.0f, 2.0f, 1000, 1000, false, OSCILLATOR});
	float_interpolaters.push_back(Interpolator<float>{&elements[1]->get_scale().y, 0.75f, 1.5f, 2000, 2000, false, OSCILLATOR});

	float_interpolaters.push_back(Interpolator<float>{&elements[0]->get_scale().x, 1.02f, 2.04f, 1000, 1000, false, OSCILLATOR});
	float_interpolaters.push_back(Interpolator<float>{&elements[0]->get_scale().y, 0.765f, 1.53f, 2000, 2000, false, OSCILLATOR});
}

void Main_Menu::handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_KEYDOWN:
		{
			switch(event.key.keysym.sym)
			{
				case SDLK_RETURN:
				{
					Game::increment_state();
				} break;
			}
		} break;
	}
	Game_State::handle_event(event);
}
