#ifndef __MODULESCENEMAIN_H__
#define __MODULESCENEMAIN_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleSceneMain : public Module
{
public:
	ModuleSceneMain(bool active = true);
	~ModuleSceneMain();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* logoTexture = nullptr;
	SDL_Texture* background = nullptr;
	SDL_Texture* letters = nullptr;
	SDL_Texture* radioTexture = nullptr;
	SDL_Texture* background2 = nullptr;
	Animation logo;
	Animation car;
	Animation palm;
	Animation insertCoins;
	Animation pressStart;
	Animation radioLeds;
	vector<SDL_Rect> radioNum;
	vector<SDL_Rect> radioHand;
	vector<SDL_Rect> radioMusic;

private:
	float countdown;
	unsigned int music;
	unsigned int audioCoin, audioWave;
	bool fxWavePlayed;
};

#endif // __MODULESCENEMAIN_H__