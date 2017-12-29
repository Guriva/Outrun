#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include <time.h>

enum InclPlayer {
	UP,
	STRAIGHT,
	DOWN,

	MAXINCL
};

enum DirPlayer {
	LEFTMOST,
	LEFT,
	FRONT,
	RIGHT,
	RIGHTMOST,

	MAXDIR
};

enum StatePlayer
{
	PREPARING,
	ONROAD,
	ENDING
};

enum StateWheel
{
	NORMAL,
	SMOKE,
	SAND
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void UpdatePlayerPreparing();
	void UpdatePlayerOnRoad();

private:
	void CheckWheels();

public:
	float speed, maxSpeed, lowAccel, highAccel, time;
	float thresholdX, varThresholdX, forceX;
	bool gear;
	InclPlayer inclination;
	DirPlayer direction;
	StatePlayer playerState;
	StateWheel wheelL;
	StateWheel wheelR;
	SDL_Texture* car = nullptr;
	SDL_Texture* carPrep = nullptr;
	SDL_Texture* carEffects = nullptr;
	Animation* current_animation = nullptr;
	Animation preparingAnim;
	Animation straight;
	Animation straightleft;
	Animation straightleftMost;
	Animation straightright;
	Animation straightrightMost;
	Animation up;
	Animation upleft;
	Animation upleftMost;
	Animation upright;
	Animation uprightMost;
	Animation down;
	Animation downleft;
	Animation downleftMost;
	Animation downright;
	Animation downrightMost;
	Animation* carStates[MAXINCL][MAXDIR];
	Animation carSmokeL;
	Animation carSmokeR;
	Animation carSandL;
	Animation carSandR;
	clock_t tick_timer;
};

#endif