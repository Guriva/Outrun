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
	SMALLCOLLISION,
	MEDIUMCOLLISION,
	AUTO,
	PlayerGAMEOVER,
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

	void resetCounters();

private:
	void UpdatePlayerPreparing();
	void UpdatePlayerOnRoad();
	void UpdatePlayerSCol();
	void UpdatePlayerMCol();
	void UpdatePlayerAuto();
	void UpdatePlayerEnding();
	void CheckWheels();

public:
	unsigned int speedSound, slideSound;
	bool speedSoundAct, slideSoundAct;
	float speed, maxSpeed, lowAccel, highAccel, time;
	float thresholdX, varThresholdX, forceX;
	float offsetCrash1;
	float prepPos, sinDif, prepPosAct;
	float lastSlide;
	int score;
	bool gear;
	InclPlayer inclination;
	DirPlayer direction;
	StatePlayer playerState;
	StateWheel wheelL;
	StateWheel wheelR;
	SDL_Texture* car = nullptr;
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
	Animation crash1;
	Animation crash2;
	Animation crash21;
	Animation endSequence;
	clock_t tick_timer;
};

#endif // __MODULEPLAYER_H__