#include "renderable.hpp"

class GameState : public Renderable {
	public:
	GameState(SDL_Texture* world_texture);
	virtual ~GameState();

	virtual void update() = 0;
	virtual void render() = 0;

	virtual void init()   = 0;
	virtual void clear()  = 0;
};
