#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace audio
{
	void update();
	void init();
	void clear();
	void toggle_pause();
	void pause();
	void unpause();
};
