#ifndef __ROAD_H__
#define __ROAD_H__

#include "Module.h"
#include <vector>

using namespace std;

class Line;
struct SDL_Texture;

class Road
{
public:
	Road();
	~Road();

	bool InitRoad();
	void RenderRoad(float time);
	bool CleanUp();

private:
	void AddSegment(float curve, float y, bool mirror);
	void AddRoad(int enter, int hold, int leave, float curve, float y, bool mirror);
	void AddStraight(int num);
	void AddCurve(int num, float curve, bool mirror);
	void AddHill(int num, float y);

private:
	SDL_Texture* layout = nullptr;
	vector<Line*> lines;
	float cameraDistance;
	int position;
	SDL_Color sand, road, rumble, lane;
	int trackLength;
	float playerX;
	int playerY, playerZ;

	float fov, cameraHeight, drawDistance;
	float segmentL, rumbleL;
	int roadLanes, roadDistance;
	short lineW;

	int dist3, dist4, dist5, dist6, dist7, dist8;

};

#endif // __ROAD_H__