#include "Globals.h"
#include "Line.h"

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
	xScreen = (SCREEN_WIDTH / 2) + ((SCREEN_WIDTH / 2) * ((xWorld - cameraX) * scale));
	yScreen = (SCREEN_HEIGHT / 2) - ((SCREEN_HEIGHT / 2) * ((yWorld - cameraY) * scale));
	wScreen = (SCREEN_WIDTH / 2) * ROAD_WIDTH * scale;
}