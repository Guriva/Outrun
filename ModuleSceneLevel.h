#ifndef __MODULESCENELEVEL_H__
#define __MODULESCENELEVEL_H__

#include "Module.h"
#include <ctime>
#include <vector>

using namespace std;

class Line;
class Road;
struct SDL_Texture;

enum SceneLevelState
{
	COUNTDOWN,
	RUNNING,
	GAMEOVER,
	FINISH
};

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel(bool active = true);
	~ModuleSceneLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	float time, countdownTimer, gameoverTimer;
	bool semaphorOne, semaphorTwo, semaphorThree;
	unsigned int semaphorSignal1, semaphorSignal2;
	Road* road;
	clock_t tick_timer;
	SceneLevelState actualState;
};

#endif // __MODULESCENELEVEL_H__