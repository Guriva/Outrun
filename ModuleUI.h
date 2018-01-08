#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "Animation.h"
#include <ctime>
#include <vector>

struct SDL_Texture;

enum UIState
{
	UIInit,
	UIPlay,
	UIFinish,
	UIGameOver
};

class ModuleUI : public Module
{
public:
	ModuleUI(bool active = true);
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* layout = nullptr;
	SDL_Texture* turbo = nullptr;
	SDL_Texture* spritesUI = nullptr;
	clock_t tick_timer;
	int score, gear;
	float speed, maxSpeed, turboIndex;
	float totalTime, time, timeLeft, lapTime, checkpointTimer, finishTimer, lastLapTime;
	float bonusTime, bonusTimeSub;
	bool checkpoint, savedTime;
	UIState uiState;
	vector<SDL_Rect> turboRect;
	SDL_Rect gameoverUI;
	SDL_Rect endUI;
	Animation extendPlay;
};

#endif // __MODULEUI_H__