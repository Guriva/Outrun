#include "Globals.h"
#include "Line.h"
#include <cmath>

using namespace std;

Line::Line()
{
	xWorld = yWorld = zWorld = curve = 0;
}

Line::~Line()
{}

void Line::projection(int cameraX, int cameraY, int cameraZ, float cameraD)
{
	//scale = (zWorld - cameraZ != 0 ? cameraD / (zWorld - cameraZ) : cameraD);
	xCamera = xWorld - cameraX;
	yCamera = yWorld - cameraY;
	zCamera = zWorld - cameraZ;
	scale = cameraD / zCamera;
	xScreen = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 2) * xCamera * scale;
	yScreen = (int)(SCREEN_HEIGHT / 2) - (int)(SCREEN_HEIGHT / 2) * yCamera * scale;
	wScreen = scale * ROAD_WIDTH * SCREEN_WIDTH / 2;
}