#ifndef __MODULESCENELEVEL_H__
#define __MODULESCENELEVEL_H__

#include "Module.h"
#include <ctime>
#include <vector>

using namespace std;

class Line;
class Road;
struct SDL_Texture;

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel(bool active = true);
	~ModuleSceneLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	float time;
	Road* road;
	clock_t tick_timer;
};

#endif // __MODULESCENELEVEL_H__