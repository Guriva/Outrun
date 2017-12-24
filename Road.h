#ifndef __ROAD_H__
#define __ROAD_H__

#include "Module.h"
#include <vector>

using namespace std;

class Line;
struct SDL_Texture;

enum playerR
{
	LEFTROAD,
	RIGHTROAD
};

class Road
{
public:
	Road();
	~Road();

	bool InitRoad();
	void RenderRoad(float time);
	bool CleanUp();

private:
	void AddSegment(float curve, float y, bool mirror, float dist);
	void AddRoad(int enter, int hold, int leave, float curve, float y, bool mirror, int distance);
	void AddStraight(int num, bool mirror, int distance);
	void AddCurve(int num, float curve, bool mirror, int distance, int length);
	void AddHill(int num, float y, int distance, int length);

private:
	SDL_Texture* layout = nullptr;
	vector<Line*> lines;
	float cameraDistance;
	int position;
	SDL_Color sand, road, rumble, lane;
	int trackLength;
	float playerX;
	int playerY, playerZ;
	playerR playerRoad;

	float fov, cameraHeight, drawDistance;
	float segmentL, rumbleL;
	int roadLanes, roadDistance;
	short lineW;

	int dist3, dist4, dist5, dist6, dist7, dist8, distM;

};

#endif // __ROAD_H__