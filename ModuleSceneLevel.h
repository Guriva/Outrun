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
	update_status Update(float time);
	bool CleanUp();

private:
	void AddSegment(float curve, float y);
	void AddRoad(int enter, int hold, int leave, float curve, float y);
	void AddStraight(int num);
	void AddCurve(int num, float curve);
	void AddHill(int num, float y);
	void RenderRoad(const Line& baseLine, float x, float dx, int maxY);
public:

private:
	vector<Line*> lines;
	float cameraDistance;
	int position;
	SDL_Color sand, road, rumble, lane;
	int trackLength;
	int playerY, playerZ;
};

#endif // __MODULESCENELEVEL_H__