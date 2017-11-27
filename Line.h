#ifndef __LINE_H__
#define __LINE_H__

class Line
{
public:

	Line();
	~Line();

	void projection(int cameraX, int cameraY, int cameraZ, float cameraD);

public:
	float xCamera, yCamera, zCamera;
	float xWorld, yWorld, zWorld;
	float xScreen, yScreen, wScreen;
	float scale, curve;
};

#endif // __LINE_H__