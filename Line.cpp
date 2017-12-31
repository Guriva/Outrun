#include "Application.h"
#include "Globals.h"
#include "Line.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include <cmath>

using namespace std;

Line::Line()
{
	p1.xWorld = p1.yWorld = p1.zWorld = p11.xWorld = p11.yWorld = p11.zWorld = 0;
	p2.xWorld = p2.yWorld = p2.zWorld = p21.xWorld = p21.yWorld = p21.zWorld = 0;
	curve = distance = clip = 0.f;
	light = mirror = false;
	lineProps.reserve(2);
	offsetsX.reserve(2);
	offsetsY.reserve(2);
	sides.reserve(2);
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

void Line::renderProps(SDL_Texture* text, int i)
{
	PointLine p = p1;
	if (sides[i])
		p = p11;

	float spriteX = p.xScreen + (offsetsX[i] * p.scale * ROAD_WIDTH * SCREEN_WIDTH / 2);
	float spriteY = p.yScreen + (offsetsY[i] * p.scale * 1000.f * SCREEN_HEIGHT / 2);
	SDL_Rect rectDest;
	fPoint pivot;

	if (offsetsX[i] >= 0)
	{
		rectDest = lineProps[i]->animRight.GetCurrentFrame();
		pivot = lineProps[i]->pivotR;
	}

	else
	{
		rectDest = lineProps[i]->animLeft.GetCurrentFrame();
		pivot = lineProps[i]->pivotL;
	}

	float destW = (rectDest.w * p.scale * SCREEN_WIDTH / 2) * ((0.3f * (1.f / 170.f)) * ROAD_WIDTH);
	float destH = (rectDest.h * p.scale * SCREEN_WIDTH / 2) * ((0.3f * (1.f / 170.f)) * ROAD_WIDTH);
		
	//If has to be clipped
	if (clip < spriteY)
	{
		float clipH = MAX(0, clip - (spriteY - (destH*3.43f*lineProps[i]->scale)));
		float clipHPerc = (clipH / (destH*3.43f*lineProps[i]->scale));
		rectDest.h = (int)(rectDest.h * clipHPerc);
		spriteY = clip;
		destH *= clipHPerc;
	}

	if (rectDest.h > 0)
		App->renderer->Blit(text, (int)spriteX, (int)(spriteY + SCREEN_Y_OFFSET), &(rectDest), 1.f, { (destW / rectDest.w)*3.2f*lineProps[i]->scale, (destH / rectDest.h)*3.43f*lineProps[i]->scale }, pivot);
}