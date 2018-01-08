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

void Line::projection(PointLine &p, int cameraX, int cameraY, int cameraZ, float cameraD) const
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

void Line::RenderProps(SDL_Texture* text, int i) const
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

void Line::RenderCars(SDL_Texture* text, const Car* car) const
{
	PointLine p = p1;
	PointLine px = p2;
	if (car->side)
	{
		p = p11;
		px = p21;
	}

	float perc = (float)(((int)(car->zPos) % (int)SEGMENT_LENGTH) / (float)SEGMENT_LENGTH);
	float scaleOffset = p.scale + (px.scale - p.scale)*perc;
	float xOffset = p.xScreen + (px.xScreen - p.xScreen)*perc;
	float yOffset = p.yScreen + (px.yScreen - p.yScreen)*perc;

	float spriteX = xOffset + (car->offset * scaleOffset * ROAD_WIDTH * SCREEN_WIDTH / 2);
	float spriteY = yOffset;
	SDL_Rect rectDest;
	fPoint pivot = { 0.5f, 1.f };
	rectDest = car->current_anim->GetCurrentFrame();

	float destW = (rectDest.w * scaleOffset * SCREEN_WIDTH / 2) * ((0.3f * (1.f / 170.f)) * ROAD_WIDTH);
	float destH = (rectDest.h * scaleOffset * SCREEN_WIDTH / 2) * ((0.3f * (1.f / 170.f)) * ROAD_WIDTH);

	//If has to be clipped
	if (clip < spriteY)
	{
		float clipH = MAX(0, clip - (spriteY - (destH*3.43f*1.2f)));
		float clipHPerc = (clipH / (destH*3.43f*1.2f));
		rectDest.h = (int)(rectDest.h * clipHPerc);
		spriteY = clip;
		destH *= clipHPerc;
	}

	if (rectDest.h > 0)
		App->renderer->Blit(text, (int)spriteX, (int)(spriteY + SCREEN_Y_OFFSET), &(rectDest), 1.f, { (destW / rectDest.w)*3.2f*1.2f, (destH / rectDest.h)*3.43f*1.2f }, pivot);
}