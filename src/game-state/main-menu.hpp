#include <vector>

#include "game-state.hpp"
#include "timer_animation.hpp"
#include "vectors.hpp"

class UI_Base;
class MainMenu : public GameState
{
	public:
	MainMenu(SDL_Renderer* renderer);
	~MainMenu();

	void update();
	void render();

	void init();
	void clear();

	void handle_event(SDL_Event event);

	void push_element(UI_Base* element);
	UI_Base* get_element(size_t index);

	private:
	std::vector<UI_Base*> elements;
	Timer_Animation<Ivec> position_animation;
};
