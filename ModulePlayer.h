#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"

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

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:
	float xPos, xSpeed;
	float speed, maxSpeed, lowAccel, highAccel;
	float thresholdX, varThresholdX;
	InclPlayer inclination;
	DirPlayer direction;
	SDL_Texture* car = nullptr;
	Animation* current_animation = nullptr;
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
};

#endif