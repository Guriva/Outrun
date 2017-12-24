#include "Application.h"
#include "Road.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "Line.h"
#include "Globals.h"
#include "Util.h"

Road::Road()
{
	//Road parameters
	fov = 120.f;
	cameraHeight = 800.f;
	drawDistance = 200;
	segmentL = 150;
	rumbleL = 3.f;
	roadLanes = 3;
	lineW = 20;
	//Initial position
	cameraDistance = 1 / tan((float)((fov / 2.f) * M_PI / 180.0f));
	position = 0;
	playerX = 0;
	playerZ = (int)(cameraHeight * cameraDistance) + 260;
	playerRoad = LEFTROAD;
	//Set distances for road lanes
	dist3 = 0;
	dist4 = dist3 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist5 = dist4 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist6 = dist5 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist7 = dist6 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist8 = dist7 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	distM = dist8 + ((int)ROAD_WIDTH * 16 / 27)*7 + ((int)ROAD_WIDTH / 18)*7;
	roadDistance = 3200;
}

Road::~Road()
{}

// Load assets
bool Road::InitRoad()
{
	LOG("Loading level scene");

	//Load textures
	layout = App->textures->Load("Textures/Level/layoutLevel.png");

	//Create Road

	AddStraight(20, false, dist8);
	AddHill(10, -5, dist8, 1);
	AddHill(5,60,dist7, 28);
	AddCurve(100, -1.5, false, dist7, 2);
	AddStraight(26,false,dist7);
	AddRoad(50, 50, 0, 1.5, 0, false, dist7);
	AddRoad(0, 100, 0, 1.5, 20, false, dist7);
	AddRoad(0, 50, 100, 1.5, -10, false, dist7);
	AddHill(40, 20, dist6, 1);
	AddRoad(30, 60, 0, 0, -15, false, dist6);
	AddRoad(0, 170, 85, -1.5, 0, false, dist6);
	AddStraight(50, false, dist6);
	AddCurve(60, -3, false, dist6, 2);
	AddStraight(70, false, dist6);
	AddCurve(20, 3, false, dist6, 8);
	AddHill(25, -10, dist6, 2);
	AddRoad(20, 40, 0, -3, 10, false, dist6);
	AddRoad(0, 80, 0, -3, -5, false, dist6);
	AddRoad(0, 70, 0, -3, 15, false, dist6);
	AddRoad(0, 50, 20, -3, 0, false, dist6);
	AddStraight(100, false, dist6);
	AddCurve(30,-3,false,dist6,2);
	AddStraight(30, false, dist6);
	AddStraight(30,false,dist5);
	AddCurve(10,3,false,dist5,3);
	AddRoad(10,20,10,-3,5,false,dist5);
	AddRoad(10,40,20,3,7,false,dist4);
	AddStraight(10,false,dist4);
	AddStraight(50,false,dist3);
	AddHill(10,5,dist3,2);
	AddHill(10,-5,dist3,2);
	AddHill(10, 5, dist3, 2);
	AddRoad(0, 400, 50, -3, 0, true, dist3);
	AddStraight(100, true, distM);
	//AddCurve(85, -1.5, false, dist6, 1);

	//AddStraight(100, false, dist7);
	//AddStraight(50, false, dist5);
	//AddStraight(50, false, dist5);
	//AddStraight(20, false, dist3);
	//AddStraight(100, false, dist3);
	//AddCurve(100, -3, true, dist3);
	//AddStraight(100, true, distM);

	trackLength = (int)(lines.size() * segmentL);

	return true;
}

// UnLoad assets
bool Road::CleanUp()
{
	LOG("Unloading level scene");
	//TODO

	return true;
}

void Road::RenderRoad(float time)
{
	//Update player position
	position += (int)(App->player->speed);
	while (position >= trackLength)
		position -= trackLength;
	while (position < 0)
		position += trackLength;

	//Calculate deviation on x for curves
	Line* baseLine = lines[(int)(position / segmentL) % lines.size()];
	int maxY = SCREEN_HEIGHT;
	float percent = (float)((position % (int)segmentL) / segmentL);
	float difX = -(baseLine->curve * percent);
	float sumX = 0;

	//Calculate playerY for hills
	Line* playerLine = lines[(int)((position + playerZ) / segmentL) % lines.size()];
	float playerPerc = (float)(((position + playerZ) % (int)segmentL) / segmentL);
	playerY = (int)(playerLine->p1.yWorld + (playerLine->p2.yWorld - playerLine->p1.yWorld) * playerPerc);
	Line* l;

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		playerX -= (App->player->speed / App->player->maxSpeed) * 2 * time;
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		playerX += (App->player->speed / App->player->maxSpeed) * 2 * time;

	playerRoad = (abs(playerLine->p1.xCamera) <= abs(playerLine->p11.xCamera) ? LEFTROAD : RIGHTROAD);

	switch (playerRoad)
	{
	case LEFTROAD:
		
		break;
	case RIGHTROAD:
		if (roadDistance != playerLine->distance)
		{
			playerX += (playerLine->distance - roadDistance) / (float)ROAD_WIDTH;
		}
		break;
	}

	roadDistance = (int)playerLine->distance;

	//Render sky background
	App->renderer->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 148, 255, 255);

	//Render second background

	//Render third background

	for (int n = 0; n < drawDistance; n++) {
		l = lines[(baseLine->index + n) % lines.size()];

		l->light ? sand = { 230, 214, 197, 255 } : sand = { 239, 222, 206, 255 };
		l->light ? road = { 156, 156, 156, 255 } : road = { 148, 148, 148, 255 };
		l->light ? rumble = { 247, 247, 247, 255 } : rumble = { 148, 148, 148, 255 };
		l->light ? lane = { 156, 156, 156, 255 } : lane = { 247, 247, 247, 255 };

		l->projection(l->p1, (int)((playerX * ROAD_WIDTH) - sumX), (int)((float)cameraHeight + playerY), position, cameraDistance);
		l->projection(l->p2, (int)((playerX * ROAD_WIDTH) - sumX - difX), (int)((float)cameraHeight + playerY), position, cameraDistance);

		if (l->mirror)
		{
			l->projection(l->p11, (int)((playerX * ROAD_WIDTH) + sumX - roadDistance), (int)((float)cameraHeight + playerY), position, cameraDistance);
			l->projection(l->p21, (int)((playerX * ROAD_WIDTH) + sumX + difX - roadDistance), (int)((float)cameraHeight + playerY), position, cameraDistance);
		}
		else
		{
			l->projection(l->p11, (int)((playerX * ROAD_WIDTH) - sumX - roadDistance), (int)((float)cameraHeight + playerY), position, cameraDistance);
			l->projection(l->p21, (int)((playerX * ROAD_WIDTH) - sumX - difX - roadDistance), (int)((float)cameraHeight + playerY), position, cameraDistance);
		}

		sumX += difX;
		difX += l->curve;

		if ((l->p1.zCamera <= cameraDistance) || (l->p2.yScreen >= maxY))
			continue;

		short x1 = (short)l->p1.xScreen;
		short x2 = (short)l->p2.xScreen;
		short y1 = (short)l->p1.yScreen;
		short y2 = (short)l->p2.yScreen;
		short w1 = (short)l->p1.wScreen;
		short w2 = (short)l->p2.wScreen;

		short x11 = (short)l->p11.xScreen;
		short x21 = (short)l->p21.xScreen;
		short y11 = (short)l->p11.yScreen;
		short y21 = (short)l->p21.yScreen;
		short w11 = (short)l->p11.wScreen;
		short w21 = (short)l->p21.wScreen;

		App->renderer->DrawPoly4(0, y1, SCREEN_WIDTH, y1, SCREEN_WIDTH, y2, 0, y2, sand);
		App->renderer->DrawPoly4(x1 - w1, y1, x1 + w1, y1, x2 + w2, y2, x2 - w2, y2, road);
		App->renderer->DrawPoly4(x11 - w11, y11, x11 + w11, y11, x21 + w21, y21, x21 - w21, y21, road);

		App->renderer->DrawPoly4(x1 - w1 - (int)(w1 / 7), y1, x1 + w1 + (int)(w1 / 7), y1, x2 + w2 + (int)(w2 / 7), y2, x2 - w2 - (int)(w2 / 7), y2, rumble);
		App->renderer->DrawPoly4(x11 - w11 - (int)(w11 / 7), y11, x11 + w11 + (int)(w11 / 7), y11, x21 + w21 + (int)(w21 / 7), y21, x21 - w21 - (int)(w21 / 7), y21, rumble);

		//Draw lines in road lanes (order matters for joining them together)
		App->renderer->DrawPoly4(x1 - w1, y1, x1 + w1, y1, x2 + w2, y2, x2 - w2, y2, lane);
		App->renderer->DrawPoly4(x11 - w11, y11, x11 + w11, y11, x21 + w21, y21, x21 - w21, y21, lane);

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18), y1, x1 + w1 - (w1 / 18), y1, x2 + w2 - (w2 / 18), y2, x2 - w2 + (w2 / 18), y2, road);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18), y11, x11 + w11 - (w11 / 18), y11, x21 + w21 - (w21 / 18), y21, x21 - w21 + (w21 / 18), y21, road);

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18) + (w1 * 16 / 27), y1, x1 + w1 - (w1 / 18) - (w1 * 16 / 27), y1, x2 + w2 - (w2 / 18) - (w2 * 16 / 27), y2, x2 - w2 + (w2 / 18) + (w2 * 16 / 27), y2, lane);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18) + (w11 * 16 / 27), y11, x11 + w11 - (w11 / 18) - (w11 * 16 / 27), y11, x21 + w21 - (w21 / 18) - (w21 * 16 / 27), y21, x21 - w21 + (w21 / 18) + (w21 * 16 / 27), y21, lane);

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18)*2 + (w1 * 16 / 27), y1, x1 + w1 - (w1 / 18)*2 - (w1 * 16 / 27), y1, x2 + w2 - (w2 / 18)*2 - (w2 * 16 / 27), y2, x2 - w2 + (w2 / 18)*2 + (w2 * 16 / 27), y2, road);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18) * 2 + (w11 * 16 / 27), y11, x11 + w11 - (w11 / 18) * 2 - (w11 * 16 / 27), y11, x21 + w21 - (w21 / 18) * 2 - (w21 * 16 / 27), y21, x21 - w21 + (w21 / 18) * 2 + (w21 * 16 / 27), y21, road);

		maxY = (int)(l->p2.yScreen);
	}

	//Render layout
	App->renderer->Blit(layout, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
}

void Road::AddSegment(float curve, float y, bool mirror, float dist)
{
	int n = (int)lines.size();
	Line* l = new Line();

	l->index = n;
	l->p1.zWorld = (float)(n * segmentL);
	l->p11.zWorld = l->p1.zWorld;
	l->p1.yWorld = (lines.size() == 0 ? 0 : lines[lines.size() - 1]->p2.yWorld);
	l->p11.yWorld = l->p1.yWorld;
	l->p2.zWorld = (float)((n + 1) * segmentL);
	l->p21.zWorld = l->p2.zWorld;
	l->p2.yWorld = y;
	l->p21.yWorld = l->p2.yWorld;
	l->light = (int)((n / rumbleL)) % 2;
	l->curve = curve;
	l->mirror = mirror;
	l->distance = dist;
	lines.push_back(l);
}

void Road::AddRoad(int enter, int hold, int leave, float curve, float y, bool mirror, int distance)
{
	float firstY, dist, distPerc;
	float total = (float)(enter + hold + leave);
	if (mirror)
	{
		firstY = (lines.size() == 0 ? 0 : lines[lines.size() - 1]->p2.yWorld);
		dist = lines[lines.size() - 1]->distance;
		distPerc = (float)((distM - dist)) / total;
	}
	else
	{
		if (lines.size() == 0)
		{
			firstY = 0;
			dist = (float)distance;
			distPerc = 0;
		}
		else
		{
			firstY = lines[lines.size() - 1]->p2.yWorld;
			dist = lines[lines.size() - 1]->distance;
			distPerc = (float)((distance - dist)) / total;
		}
	}

	float endY = firstY + y * segmentL;
	int n;

	for (n = 0; n < enter; ++n)
	{
		dist += (int)distPerc;
		AddSegment(EaseIn(0, curve, (float)n / enter), EaseInOut(firstY, endY, (float)n / total), mirror, (int)dist);
	}
		
	for (n = 0; n < hold; ++n)
	{
		dist += (int)distPerc;
		AddSegment(curve, EaseInOut(firstY, endY, (float)(enter + n) / total), mirror, (int)dist);
	}
		
	for (n = 0; n < leave; ++n)
	{
		dist += (int)distPerc;
		AddSegment(EaseInOut(curve, 0, (float)n / leave), EaseInOut(firstY, endY, (float)(enter + hold + n) / total), mirror, (int)dist);
	}
		
}

void Road::AddStraight(int num, bool mirror, int distance)
{
	AddRoad(num, num, num, 0, 0, mirror, distance);
}

void Road::AddCurve(int num, float curve, bool mirror, int distance, int length)
{
	AddRoad(num, num*length, num, curve, 0, mirror, distance);
}

void Road::AddHill(int num, float y, int distance, int length)
{
	AddRoad(num, num*length, num, 0, y, false, distance);
}