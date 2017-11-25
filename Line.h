#ifndef __LINE_H__
#define __LINE_H__

class Line
{
public:

	Line();
	~Line();

	void projection(int cameraX, int cameraY, int cameraZ, float cameraD);

public:

	float xWorld, yWorld, zWorld;
	float xScreen, yScreen, wScreen, scale;
};

#endif // __LINE_H__