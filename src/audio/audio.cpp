#include "audio.hpp"
#include "error.hpp"
#include "settings.hpp"

namespace audio
{
Mix_Music* music;

void update()
{
	if(!Mix_PlayingMusic())
	{
		Mix_PlayMusic(music, -1);
	}
	int volume = Settings::get_setting(Settings::all, "volume")->data;
	Mix_VolumeMusic(volume * MIX_MAX_VOLUME / 100.0f);
}

void init()
{
	Error(SDL_Init(SDL_INIT_AUDIO) < 0, { "Failed to initialize audio" });
	// Initialize SDL_mixer
	Error(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0,
		  { "SDL_mixer could not initialize! SDL_mixer Error: ",
			Mix_GetError() });

	music = Mix_LoadMUS("res/audio/test.wav");
	Error(music == NULL, { "failed to load audio file" });
}

void clear()
{
	Mix_FreeMusic(music);
	Mix_Quit();
}

void toggle_pause()
{
	if(Mix_PausedMusic())
	{
		Mix_ResumeMusic();
	}
	else
	{
		Mix_PauseMusic();
	}
}

void pause()
{
	Mix_PauseMusic();
}

void unpause()
{
	Mix_ResumeMusic();
}
};
