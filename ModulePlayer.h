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
	void OnCollision(Collider* c1, Collider* c2);

public:
	float speed, maxSpeed, lowAccel, highAccel, time;
	float thresholdX, varThresholdX, forceX;
	InclPlayer inclination;
	DirPlayer direction;
	StatePlayer playerState;
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
	Animation carSmoke;
	clock_t tick_timer;
	Collider *col;
};

#endif