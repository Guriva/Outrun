#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "Line.h"
#include "ModulePlayer.h"
#include "Util.h"
#include <math.h>

using namespace std;

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{
	cameraDistance = 1 / tan((float)((FOV / 2.f) * M_PI / 180.0f));
	position = 0;
	playerZ = CAMERA_HEIGHT * cameraDistance;
}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading level scene");

	AddHill(100, 10);
	AddStraight(100);
	AddHill(25, 20);
	AddHill(25, -10);
	AddCurve(100, 2);
	AddStraight(100);
	AddStraight(100);
	AddStraight(100);

	trackLength = lines.size() * SEGMENT_LENGTH;

	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading level scene"); 

	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update(float time)
{
	position += (int)(App->player->speed * time);
	while (position >= trackLength)
		position -= trackLength;
	while (position < 0)
		position += trackLength;

	//Render sky background
	App->renderer->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 148, 255, 255);

	//Render second background

	//Render third background

	//Calculate deviation on x for curves
	Line* baseLine = lines[(position / SEGMENT_LENGTH) % lines.size()];
	int maxY = SCREEN_HEIGHT;
	float percent = (float)((position % SEGMENT_LENGTH) / SEGMENT_LENGTH);
	float dx = -(baseLine->curve * percent);
	float x = 0;

	//Calculate playerY for hills
	Line* playerLine = lines[((position + playerZ) / SEGMENT_LENGTH) % lines.size()];
	float playerPerc = (float)(((position + playerZ) % SEGMENT_LENGTH) / SEGMENT_LENGTH);
	playerY = playerLine->p1.yWorld + (playerLine->p2.yWorld - playerLine->p1.yWorld) * playerPerc;
	//RenderRoad(*baseLine, x, dx, maxY);
	Line* l;

	for (int n = 0; n < DRAW_DISTANCE; n++) {
		l = lines[(baseLine->index + n) % lines.size()];

		l->projection(l->p1, (int)((App->player->playerX) - x), CAMERA_HEIGHT + playerY, position, cameraDistance);
		l->projection(l->p2, (int)((App->player->playerX) - x - dx), CAMERA_HEIGHT + playerY, position, cameraDistance);

		x += dx;
		dx += l->curve;

		if ((l->p1.zCamera <= cameraDistance) || (l->p2.yScreen >= maxY))
			continue;

		l->light ? sand = { 230, 214, 197, 255 } : sand = { 239, 222, 206, 255 };
		l->light ? road = { 156, 156, 156, 255 } : road = { 148, 148, 148, 255 };
		l->light ? rumble = { 247, 247, 247, 255 } : rumble = { 148, 148, 148, 255 };
		l->light ? lane = { 156, 156, 156, 255 } : lane = { 247, 247, 247, 255 };


		short x1 = (short)l->p1.xScreen;
		short x2 = (short)l->p2.xScreen;
		short y1 = (short)l->p1.yScreen;
		short y2 = (short)l->p2.yScreen;
		short w1 = (short)l->p1.wScreen;
		short w2 = (short)l->p2.wScreen;

		App->renderer->DrawPoly4(0, y1, SCREEN_WIDTH, y1, SCREEN_WIDTH, y2, 0, y2, sand);
		App->renderer->DrawPoly4(x1-w1, y1, x1+w1, y1, x2+w2, y2, x2-w2, y2, road);
		App->renderer->DrawPoly4(x1 - w1 - (int)(w1 / 6), y1, x1 - w1, y1, x2 - w2, y2, x2 - w2 - (int)(w2 / 6), y2, rumble);
		App->renderer->DrawPoly4(x1 + w1 + (int)(w1 / 6), y1, x1 + w1, y1, x2 + w2, y2, x2 + w2 + (int)(w2 / 6), y2, rumble);
		App->renderer->DrawPoly4(x1-w1, y1, x1-w1+(w1 / 24), y1, x2-w2+(w2 / 24), y2, x2-w2, y2, lane);
		App->renderer->DrawPoly4(x1 + w1, y1, x1 + w1 - (w1 / 24), y1, x2 + w2 - (w2 / 24), y2, x2 + w2, y2, lane);

		if (l->light == false) {
			short lw1 = w1 * 2 / ROAD_LANES;
			short lw2 = w2 * 2 / ROAD_LANES;
			short lx1 = x1 - w1;
			short lx2 = x2 - w2;

			for (int i = 1; i < ROAD_LANES; ++i) {
				App->renderer->DrawPoly4(lx1 + (lw1 * i) - (w1 / 36), y1, lx1 + (lw1 * i) + (w1 / 36), y1, lx2 + (lw2 * i) + (w2 / 36), y2, lx2 + (lw2 * i) - (w2 / 36), y2, lane);
			}
		}

		maxY = (int)(l->p2.yScreen);
	}

	return UPDATE_CONTINUE;
}

void ModuleSceneLevel::AddSegment(float curve, float y)
{
	int n = (int)lines.size();
	Line* l = new Line();

	l->index = n;
	l->p1.zWorld = (float)(n * SEGMENT_LENGTH);
	l->p1.yWorld = (lines.size() == 0 ? 0 : lines[lines.size() - 1]->p2.yWorld);
	l->p2.zWorld = (float)((n + 1) * SEGMENT_LENGTH);
	l->p2.yWorld = y;
	l->light = (n / RUMBLE_LENGTH) % 2;
	l->curve = curve;
	lines.push_back(l);
}

void ModuleSceneLevel::AddRoad(int enter, int hold, int leave, float curve, float y)
{
	float firstY = (lines.size() == 0 ? 0 : lines[lines.size() - 1]->p2.yWorld);
	float endY = firstY + y * SEGMENT_LENGTH;
	int n;
	float total = (float)(enter + hold + leave);
	for (n = 0; n < enter; ++n)
		AddSegment(EaseIn(0, curve, (float)n/enter), EaseInOut(firstY, endY, (float)n/total));
	for (n = 0; n < hold; ++n)
		AddSegment(curve, EaseInOut(firstY, endY, (float)(enter + n) / total));
	for (n = 0; n < leave; ++n)
		AddSegment(EaseInOut(curve, 0, (float)n/leave), EaseInOut(firstY, endY, (float)(enter + hold + n) / total));
}

void ModuleSceneLevel::AddStraight(int num)
{
	AddRoad(num,num,num,0,0);
}

void ModuleSceneLevel::AddCurve(int num, float curve)
{
	AddRoad(num,num,num,curve,0);
}

void ModuleSceneLevel::AddHill(int num, float y)
{
	AddRoad(num, num, num, 0, y);
}


/***TODO***/
//Need for later use to render 2 roads
void ModuleSceneLevel::RenderRoad(const Line& baseLine, float x, float dx, int maxY)
{
	Line* l;

	for (int n = 0; n < DRAW_DISTANCE; n++) {
		l = lines[(baseLine.index + n) % lines.size()];

		l->projection(l->p1, (int)((App->player->playerX) - x), CAMERA_HEIGHT + playerY, position, cameraDistance);
		l->projection(l->p2, (int)((App->player->playerX) - x - dx), CAMERA_HEIGHT + playerY, position, cameraDistance);

		x += dx;
		dx += l->curve;

		if ((l->p1.zCamera <= cameraDistance) || (l->p2.yScreen >= maxY))
			continue;

		l->light ? sand = { 230, 214, 197, 255 } : sand = { 239, 222, 206, 255 };
		l->light ? road = { 156, 156, 156, 255 } : road = { 148, 148, 148, 255 };
		l->light ? rumble = { 247, 247, 247, 255 } : rumble = { 148, 148, 148, 255 };
		l->light ? lane = { 156, 156, 156, 255 } : lane = { 247, 247, 247, 255 };


		short x1 = (short)l->p1.xScreen;
		short x2 = (short)l->p2.xScreen;
		short y1 = (short)l->p1.yScreen;
		short y2 = (short)l->p2.yScreen;
		short w1 = (short)l->p1.wScreen;
		short w2 = (short)l->p2.wScreen;

		App->renderer->DrawPoly4(0, y1, SCREEN_WIDTH, y1, SCREEN_WIDTH, y2, 0, y2, sand);
		App->renderer->DrawPoly4(x1 - w1, y1, x1 + w1, y1, x2 + w2, y2, x2 - w2, y2, road);
		App->renderer->DrawPoly4(x1 - w1 - (int)(w1 / 6), y1, x1 - w1, y1, x2 - w2, y2, x2 - w2 - (int)(w2 / 6), y2, rumble);
		App->renderer->DrawPoly4(x1 + w1 + (int)(w1 / 6), y1, x1 + w1, y1, x2 + w2, y2, x2 + w2 + (int)(w2 / 6), y2, rumble);
		App->renderer->DrawPoly4(x1 - w1, y1, x1 - w1 + (w1 / 24), y1, x2 - w2 + (w2 / 24), y2, x2 - w2, y2, lane);
		App->renderer->DrawPoly4(x1 + w1, y1, x1 + w1 - (w1 / 24), y1, x2 + w2 - (w2 / 24), y2, x2 + w2, y2, lane);

		if (l->light == false) {
			short lw1 = w1 * 2 / ROAD_LANES;
			short lw2 = w2 * 2 / ROAD_LANES;
			short lx1 = x1 - w1;
			short lx2 = x2 - w2;

			for (int i = 1; i < ROAD_LANES; ++i) {
				App->renderer->DrawPoly4(lx1 + (lw1 * i) - (w1 / 36), y1, lx1 + (lw1 * i) + (w1 / 36), y1, lx2 + (lw2 * i) + (w2 / 36), y2, lx2 + (lw2 * i) - (w2 / 36), y2, lane);
			}
		}

		maxY = (int)(l->p2.yScreen);
	}
}