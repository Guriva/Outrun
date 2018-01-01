#ifndef __ROAD_H__
#define __ROAD_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include <vector>

using namespace std;

class Line;
struct SDL_Texture;

enum playerR
{
	LEFTROAD,
	RIGHTROAD
};

struct Car
{
	Animation* current_anim;
	Animation left;
	Animation right;
	float offset, speed, zPos;
	bool active, side;
	int lane;
	Car() : offset(0), speed(50),
		active(false), side(false),
		lane(1) {}
};

struct Prop
{
	Animation animLeft;
	Animation animRight;
	fPoint pivotL, pivotR;
	float scale;
	bool collider;
	float wCol;
	fPoint pivotColL, pivotColR;
	Prop() : pivotL({ 1.f, 1.f }), pivotR({ 0.f, 1.f }),
		scale(1.f),
		collider(false),
		wCol(0.f),
		pivotColL({ 0.5f, 1.f }), pivotColR({ 0.5f, 1.f }) {}
};

class Road
{
public:
	Road();
	~Road();

	bool Start();
	bool InitRoad();
	void UpdateRoad(float time);
	void DrawRoad();
	void ActivateAnims();
	bool CleanUp();

private:
	void AddFlagmanAnim();
	void AddSegment(float curve, float y, bool mirror, float dist);
	void AddRoad(int enter, int hold, int leave, float curve, float y, bool mirror, int distance);
	void AddStraight(int num, bool mirror, int distance);
	void AddCurve(int num, float curve, bool mirror, int distance, int length);
	void AddHill(int num, float y, int distance, int length);
	void AddProp(unsigned int line, Prop* p, float offsetX, float offsetY, bool side);
	void UpdateWheels();
	void UpdateCars();
	void CheckCarsState();
	void CheckPlayerCollision(const Line* playerLine);
	bool Collides(float x1, int w1, float x2, float w2, float scale);

private:
	SDL_Texture* layout = nullptr;
	SDL_Texture* sprites = nullptr;
	SDL_Texture* backgrounds = nullptr;
	SDL_Texture* cars = nullptr;

	SDL_Rect backgroundLvl1;
	SDL_Rect background2Lvl1;

	vector<Line*> lines;
	float cameraDistance;
	int position, iniPosition;
	SDL_Color sand, road, rumble, lane;
	int trackLength;
	float playerX, pWheelL, pWheelR, collisionDir;
	float thresholdX, varThresholdX;
	int playerY, playerZ, playerW;
	playerR playerRoad;

	float fov, cameraHeight, drawDistance, offsetXBackground1, offsetXBackground2;
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
	Prop* panel4 = nullptr;
	Prop* vulturesign = nullptr;

	Car* truck1 = nullptr;
	Car* truck2 = nullptr;
	Car* atom1 = nullptr;
	Car* atom2 = nullptr;
	Car* out1 = nullptr;
	Car* out2 = nullptr;

	vector<Car*> active;
};

#endif // __ROAD_H__