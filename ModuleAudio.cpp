#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "SDL.h"

#include "SDL_mixer.h"

using namespace std;

ModuleAudio::ModuleAudio(bool start_enabled) : Module(start_enabled)
{}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
		ret = false;

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
		ret = false;

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		ret = false;

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{
	if (music != nullptr)
		Mix_FreeMusic(music);

	for (vector<Mix_Chunk*>::iterator it = fx.begin(); it != fx.end(); ++it)
		Mix_FreeChunk(*it);

	fx.clear();
	Mix_Quit();
	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

// Play a music file
bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if (music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}
	}

	music = Mix_LoadMUS(path);

	if (music == nullptr)
		ret = false;
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
				ret = false;
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
				ret = false;
		}
	}

	return ret;
}

bool ModuleAudio::StopMusic(float fade_time)
{
	bool ret = true;

	if (music != nullptr)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}
	}

	return ret;
}

// Load WAV
unsigned int ModuleAudio::LoadFx(const char* path)
{
	unsigned int ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	fx.push_back(chunk);
	ret = fx.size() - 1;

	return ret;
}

// Play WAV
bool ModuleAudio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (id < fx.size())
	{
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}

bool ModuleAudio::PlayFxChannel(unsigned int id, int repeat, int channel)
{
	bool ret = false;

	if (id < fx.size())
	{
		Mix_PlayChannel(channel, fx[id], repeat);
		ret = true;
	}

	return ret;
}

bool ModuleAudio::StopFx()
{
	Mix_HaltChannel(-1);
	return true;
}

bool ModuleAudio::StopFxChannel(int channel)
{
	Mix_HaltChannel(channel);
	return true;
}