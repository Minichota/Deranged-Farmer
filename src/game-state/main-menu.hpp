#include <vector>

#include "game-state.hpp"
#include "vectors.hpp"

class UI_Base;
class Main_Menu : public Game_State
{
	public:
	Main_Menu(SDL_Renderer* renderer);
	~Main_Menu();

	void update();
	void render();

	void init();
	void clear();

	void handle_event(SDL_Event event);

	void push_element(UI_Base* element);
	UI_Base* get_element(size_t index);

	private:
	std::vector<UI_Base*> elements;
};
