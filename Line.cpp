#include "Globals.h"
#include "Line.h"
#include <cmath>

using namespace std;

Line::Line()
{
	xWorld = yWorld = zWorld = 0;
}

Line::~Line()
{}

void Line::projection(int cameraX, int cameraY, int cameraZ, float cameraD)
{
	//scale = (zWorld - cameraZ != 0 ? cameraD / (zWorld - cameraZ) : cameraD);
	scale = cameraD / (zWorld - cameraZ);
	xScreen = (SCREEN_WIDTH / 2) + (SCREEN_WIDTH / 2) * ((xWorld - cameraX) * scale);
	yScreen = (int)(SCREEN_HEIGHT / 2) - (int)(SCREEN_HEIGHT / 2) * ((yWorld - cameraY) * scale);
	//xScreen = (1 + scale*(xWorld - cameraX)) * SCREEN_WIDTH / 2;
	//yScreen = (1 - scale*(yWorld - cameraY)) * SCREEN_HEIGHT / 2;
	wScreen = scale * ROAD_WIDTH * SCREEN_WIDTH / 2;
}