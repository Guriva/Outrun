#ifndef __LINE_H__
#define __LINE_H__

#include <vector>
#include "Road.h"

struct PointLine {
	float xCamera, yCamera, zCamera;
	float xWorld, yWorld, zWorld;
	float xScreen, yScreen, wScreen;
	float scale;
};

class Line
{
public:

	Line();
	~Line();

	void projection(PointLine &p, int cameraX, int cameraY, int cameraZ, float cameraD);
	void RenderProps(SDL_Texture* text, int i);
	void RenderCars(SDL_Texture* text, Car* car);

public:
	int index;
	PointLine p1, p2;
	PointLine p11, p21;
	bool light, mirror;
	float curve, distance, clip;
	vector<Prop*> lineProps;
	vector<float> offsetsX;
	vector<float> offsetsY;
	vector<bool> sides;
};

#endif // __LINE_H__