#ifndef __ROAD_H__
#define __ROAD_H__

#include "Module.h"
#include "Animation.h"
#include <vector>

using namespace std;

class Line;
struct SDL_Texture;

enum playerR
{
	LEFTROAD,
	RIGHTROAD
};

struct Prop
{
	Animation animLeft;
	Animation animRight;
	float width;
};

class Road
{
public:
	Road();
	~Road();

	bool Start();
	bool InitRoad();
	void RenderRoad(float time);
	void ActivateAnims();
	bool CleanUp();

private:
	void AddFlagmanAnim();
	void AddSegment(float curve, float y, bool mirror, float dist);
	void AddRoad(int enter, int hold, int leave, float curve, float y, bool mirror, int distance);
	void AddStraight(int num, bool mirror, int distance);
	void AddCurve(int num, float curve, bool mirror, int distance, int length);
	void AddHill(int num, float y, int distance, int length);

private:
	SDL_Texture* layout = nullptr;
	SDL_Texture* sprites = nullptr;
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

	Prop* flagman = nullptr;
	Prop* man1 = nullptr;
	Prop* man2 = nullptr;
	Prop* man3 = nullptr;
	Prop* man4 = nullptr;
	Prop* man5 = nullptr;
	Prop* cameraman = nullptr;
	Prop* musicman = nullptr;
	Prop* woman1 = nullptr;
	Prop* woman2 = nullptr;
	Prop* woman3 = nullptr;
	Prop* sign75 = nullptr;
	Prop* trafficLight = nullptr;
	Prop* slow = nullptr;
	Prop* curveSlow = nullptr;
	Prop* house1 = nullptr;
	Prop* house2 = nullptr;
	Prop* house3 = nullptr;
	Prop* house4 = nullptr;
	Prop* water = nullptr;
	Prop* palm1 = nullptr;
	Prop* palm2 = nullptr;
	Prop* start = nullptr;
	Prop* people1 = nullptr;
	Prop* surf1 = nullptr;
	Prop* surf2 = nullptr;
	Prop* surf3 = nullptr;
	Prop* panel1 = nullptr;
	Prop* panel2 = nullptr;
	Prop* panel3 = nullptr;
	Prop* vulturesign = nullptr;
};

#endif // __ROAD_H__