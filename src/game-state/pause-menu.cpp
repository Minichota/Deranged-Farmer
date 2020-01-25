#include "pause-menu.hpp"
#include "error.hpp"
#include "game.hpp"
#include "interpolators.hpp"
#include "settings.hpp"
#include "ui-button.hpp"
#include "ui-image.hpp"
#include "ui-rect.hpp"
#include "ui-slider.hpp"
#include "ui-text.hpp"

Pause_Menu::Pause_Menu(SDL_Renderer* renderer) : Game_State(renderer)
{
	elements.push_back(new UI_Text(
		renderer, Ivec(400, 200), Ivec(300, 150), Fvec(1.0f, 1.0f), "PAUSED",
		"res/graphics/font.ttf", SDL_Color{ 255, 255, 255, 255 }, FILL));
	elements.push_back(new UI_Text(renderer, Ivec(400, 500), Ivec(300, 0),
								   Fvec(1.0f, 1.0f), "Press enter to continue",
								   "res/graphics/font.ttf",
								   SDL_Color{ 255, 255, 255, 255 }, NORMAL));
	elements.push_back(new UI_Button(renderer, Ivec(0, 0), Ivec(0, 0),
									 Fvec(1.0f, 1.0f), &quit,
									 SDL_Color{ 255, 255, 255, 255 }));
	elements.push_back(new UI_Text(
		renderer, Ivec(0, 0), Ivec(0, 0), Fvec(1.0f, 1.0f), "Main Menu",
		"res/graphics/font.ttf", SDL_Color{ 255, 255, 255, 255 }, NORMAL));
	elements.push_back(new UI_Image(renderer, Ivec(735, 560), Ivec(50, 50),
									Fvec(1.0f, 1.0f), FILL,
									"res/graphics/volume.png"));
	elements.push_back(new UI_Slider(
		renderer, Ivec(735, 590), Ivec(110, 10), Fvec(1.0f, 1.0f), 0, 100, 100,
		SDL_Color{ 255, 255, 255, 255 }, SDL_Color{ 127, 127, 127, 255 }));

	elements[0]->set_origin(elements[0]->get_size() / 2);
	elements[1]->set_origin(elements[1]->get_size() / 2);
	elements[2]->set_size(elements[3]->get_size());
	elements[4]->set_origin(elements[4]->get_size() / 2);
	elements[5]->set_origin(elements[5]->get_size() / 2);

	Settings::Data<int>* x = Settings::get_setting(Settings::all, "volume");
	if(x != nullptr)
	{
		dynamic_cast<UI_Slider*>(elements[5])->set_bind(&x->data);
	}
}

void quit()
{
	Game::toggle_pause();
	Game::set_state(0);
}

void Pause_Menu::init()
{
	uchar_interpolaters.push_back(Interpolator<unsigned char>{
		OSCILLATOR, &elements[1]->get_color().a, 0, 255, 750, 750 });
}

void Pause_Menu::handle_event(const SDL_Event& event)
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
