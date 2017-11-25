#ifndef __MODULESCENELEVEL_H__
#define __MODULESCENELEVEL_H__

#include "Module.h"
#include <vector>

using namespace std;

class Line;

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel(bool active = true);
	~ModuleSceneLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

private:
	vector<Line*> lines;
	float cameraDistance;
	SDL_Color sand, road, rumble, lane;
};

#endif // __MODULESCENELEVEL_H__