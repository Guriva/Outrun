#include "Globals.h"
#include "Line.h"
#include <cmath>

using namespace std;

Line::Line()
{
	p1.xWorld = p1.yWorld = p1.zWorld = p11.xWorld = p11.yWorld = p11.zWorld = 0;
	p2.xWorld = p2.yWorld = p2.zWorld = p21.xWorld = p21.yWorld = p21.zWorld = 0;
	curve = distance = 0;
	light = mirror = false;
	lineProps.reserve(2);
	offsets.reserve(2);
}

Line::~Line()
{}

void Line::projection(PointLine &p, int cameraX, int cameraY, int cameraZ, float cameraD)
{
	//scale = (zWorld - cameraZ != 0 ? cameraD / (zWorld - cameraZ) : cameraD);
	p.xCamera = p.xWorld - cameraX;
	p.yCamera = p.yWorld - cameraY;
	p.zCamera = p.zWorld - cameraZ;
	p.scale = cameraD / p.zCamera;
	p.xScreen = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 2) * p.xCamera * p.scale;
	p.yScreen = (SCREEN_HEIGHT / 2) - (SCREEN_HEIGHT / 2) * p.yCamera * p.scale;
	p.wScreen = p.scale * ROAD_WIDTH * SCREEN_WIDTH / 2;
}