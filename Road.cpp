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
	pWheelL = -20;
	pWheelR = 20;
	playerZ = (int)(cameraHeight * cameraDistance) + 241;
	playerRoad = LEFTROAD;
	//Set distances for road lanes
	dist3 = 0;
	dist4 = dist3 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist5 = dist4 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist6 = dist5 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist7 = dist6 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist8 = dist7 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	distM = dist8 + ((int)ROAD_WIDTH * 16 / 27)*7 + ((int)ROAD_WIDTH / 18)*7;
	roadDistance = 0;
}

Road::~Road()
{}

bool Road::Start()
{
	AddFlagmanAnim();
	man1 = new Prop();
	man1->animLeft.frames.push_back({ 1109, 296, 28, 61 });
	man1->animRight.frames.push_back({ 1, 105, 28, 61 });
	man2 = new Prop();
	man2->animLeft.frames.push_back({ 1080, 296, 28, 61 });
	man2->animRight.frames.push_back({ 30, 105, 28, 61 });
	man3 = new Prop();
	man3->animLeft.frames.push_back({ 1056, 296, 23, 62 });
	man3->animRight.frames.push_back({ 59, 105, 23, 62 });
	man4 = new Prop();
	man4->animLeft.frames.push_back({ 1032, 296, 23, 61 });
	man4->animRight.frames.push_back({ 83, 105, 23, 61 });
	man5 = new Prop();
	man5->animLeft.frames.push_back({ 982, 296, 20, 63 });
	man5->animRight.frames.push_back({ 136, 105, 20, 63 });
	cameraman = new Prop();
	cameraman->animLeft.frames.push_back({ 107, 105, 28, 60 });
	cameraman->animRight.frames.push_back({ 1003, 296, 28, 60 });
	musicman = new Prop();
	musicman->animLeft.frames.push_back({ 215, 105, 34, 35 });
	musicman->animRight.frames.push_back({ 215, 105, 34, 35 });
	woman1 = new Prop();
	woman1->animLeft.frames.push_back({ 965, 296, 16, 54 });
	woman1->animRight.frames.push_back({ 157, 105, 16, 54 });
	woman2 = new Prop();
	woman2->animLeft.frames.push_back({ 174, 105, 15, 56 });
	woman2->animRight.frames.push_back({ 949, 296, 15, 56 });
	woman3 = new Prop();
	woman3->animLeft.frames.push_back({ 190, 105, 24, 57 });
	woman3->animRight.frames.push_back({ 924, 296, 24, 57 });
	sign75 = new Prop();
	sign75->animLeft.frames.push_back({ 215, 141, 34, 27 });
	sign75->animRight.frames.push_back({ 215, 141, 34, 27 });
	trafficLight = new Prop();
	trafficLight->animLeft.frames.push_back({ 250, 105, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 277, 296, 74 ,128 });
	trafficLight->animLeft.frames.push_back({ 277, 296, 74 ,128 });
	trafficLight->animLeft.frames.push_back({ 277, 296, 74 ,128 });
	trafficLight->animLeft.loop = false;
	trafficLight->animLeft.speed = 0.f;
	trafficLight->animRight = trafficLight->animLeft;
	trafficLight->scale = 1.2f;
	slow = new Prop();
	slow->animLeft.frames.push_back({ 449, 105, 60, 112 });
	slow->animRight.frames.push_back({ 388, 105, 60, 112 });
	curveSlow = new Prop();
	curveSlow->animLeft.frames.push_back({ 510, 105, 60, 112 });
	curveSlow->animRight.frames.push_back({ 572, 105, 60, 112 });
	house1 = new Prop();
	house1->animLeft.frames.push_back({ 632, 105, 120, 86 });
	house1->animRight.frames.push_back({ 632, 105, 120, 86 });
	house2 = new Prop();
	house2->animLeft.frames.push_back({ 753, 105, 120, 86 });
	house2->animRight.frames.push_back({ 753, 105, 120, 86 });
	house3 = new Prop();
	house3->animLeft.frames.push_back({ 874, 105, 120, 86 });
	house3->animRight.frames.push_back({ 874, 105, 120, 86 });
	house4 = new Prop();
	house4->animLeft.frames.push_back({ 582, 296, 116, 64 });
	house4->animRight.frames.push_back({ 582, 296, 116, 64 });
	water = new Prop();
	water->animLeft.frames.push_back({ 127, 425, 244, 32 });
	water->animLeft.frames.push_back({ 127, 458, 244, 32 });
	water->animLeft.speed = 0.1f;
	water->animRight.frames.push_back({ 1, 169, 244, 32 });
	water->animRight.frames.push_back({ 1, 202, 244, 32 });
	water->animRight.speed = 0.1f;
	palm1 = new Prop();
	palm1->animLeft.frames.push_back({ 924, 360, 153, 167 });
	palm1->animRight.frames.push_back({ 995, 105, 153, 167 });
	palm1->scale = 1.2f;
	palm2 = new Prop();
	palm2->animLeft.frames.push_back({ 453, 296, 128, 79 });
	palm2->animRight.frames.push_back({ 453, 296, 128, 79 });
	start = new Prop();
	start->animLeft.frames.push_back({ 1, 234, 472, 61 });
	start->animRight.frames.push_back({ 1, 234, 472, 61 });
	start->pivotL = { 0.f, 1.f };
	start->pivotR = { 1.f, 1.f };
	people1 = new Prop();
	people1->animLeft.frames.push_back({ 474, 230, 188, 65 });
	people1->animRight.frames.push_back({ 474, 230, 188, 65 });
	surf1 = new Prop();
	surf1->animLeft.frames.push_back({ 780, 209, 51, 86 });
	surf1->animRight.frames.push_back({ 780, 209, 51, 86 });
	surf2 = new Prop();
	surf2->animLeft.frames.push_back({ 832, 209, 51, 86 });
	surf2->animRight.frames.push_back({ 832, 209, 51, 86 });
	surf3 = new Prop();
	surf3->animLeft.frames.push_back({ 884, 209, 51, 86 });
	surf3->animRight.frames.push_back({ 884, 209, 51, 86 });
	panel1 = new Prop();
	panel1->animLeft.frames.push_back({ 1, 296, 125, 169 });
	panel1->animRight.frames.push_back({ 1, 296, 125, 169 });
	panel2 = new Prop();
	panel2->animLeft.frames.push_back({ 352, 296, 100, 101 });
	panel2->animRight.frames.push_back({ 352, 296, 100, 101 });
	panel3 = new Prop();
	panel3->animLeft.frames.push_back({ 663, 215, 116, 80 });
	panel3->animRight.frames.push_back({ 663, 215, 116, 80 });
	panel4 = new Prop();
	panel4->animLeft.frames.push_back({ 325, 105, 62, 128 });
	panel4->animRight.frames.push_back({ 325, 105, 62, 128 });
	panel4->scale = 1.2f;
	vulturesign = new Prop();
	vulturesign->animLeft.frames.push_back({ 699, 296, 224, 152 });
	vulturesign->animRight.frames.push_back({ 699, 296, 224, 152 });

	return true;
}

// Load assets
bool Road::InitRoad()
{
	LOG("Loading level scene");

	//Load textures
	layout = App->textures->Load("Textures/Level/layoutLevel.png");
	sprites = App->textures->Load("Textures/Level/spriteslvl1.png");
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

	//Add elements to each line
	AddProp(5, woman3, -0.63f, 0.f);
	AddProp(5, musicman, -0.3f, 0.f);
	AddProp(5, cameraman, -0.5f, 0.f);
	AddProp(5, woman1, 0.5f, 0.f);

	AddProp(6, man1, -0.7f, 0.f);
	AddProp(6, man3, -0.5f, 0.f);
	AddProp(6, flagman, -0.3f, 0.f);
	AddProp(9, start, -1.25f, -1.8f);
	AddProp(9, trafficLight, -0.8f, 0.f);
	AddProp(9, panel4, 1.f, 0.f);
	//AddProp(9, palm1, -0.8f, 0.f);

	float sep = 1;
	for (int i = 1; i < 36; i += 3)
	{
		AddProp(i + (int)sep, palm1, -0.8f, 0.f);
		AddProp(i + (int)sep, palm1, 0.8f, 0.f);
		sep *= 1.5f;
	}
	//AddProp(240, palm1, -0.8f, 0.f);


	trackLength = (int)(lines.size() * segmentL);

	return true;
}

// UnLoad assets
bool Road::CleanUp()
{
	LOG("Unloading level scene");
	//TODO
	RELEASE(flagman);
	RELEASE(man1);
	RELEASE(man2);
	RELEASE(man3);
	RELEASE(man4);
	RELEASE(man5);
	RELEASE(cameraman);
	RELEASE(musicman);
	RELEASE(woman1);
	RELEASE(woman2);
	RELEASE(woman3);
	RELEASE(sign75);
	RELEASE(trafficLight);
	RELEASE(slow);
	RELEASE(curveSlow);
	RELEASE(house1);
	RELEASE(house2);
	RELEASE(house3);
	RELEASE(house4);
	RELEASE(water);
	RELEASE(palm1);
	RELEASE(palm2);
	RELEASE(start);
	RELEASE(people1);
	RELEASE(surf1);
	RELEASE(surf2);
	RELEASE(surf3);
	RELEASE(panel1);
	RELEASE(panel2);
	RELEASE(panel3);
	RELEASE(panel4);
	RELEASE(vulturesign);

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

	playerLine->projection(playerLine->p1, (int)((playerX * ROAD_WIDTH) - sumX), (int)((float)cameraHeight + playerY), position, cameraDistance);

	float maxY = playerLine->p1.yScreen;
	roadDistance = (int)playerLine->distance;

	UpdateWheels();

	//Render sky background
	App->renderer->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 148, 255, 255);

	//Render second background

	//Render third background

	for (int n = 0; n < drawDistance; n++) {
		l = lines[(baseLine->index + n) % lines.size()];
		l->clip = maxY;

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

		maxY = l->p2.yScreen;
	}

	//Draw cars and sprites
	for (int n = (int)(drawDistance - 1); n > 0; --n)
	{
		l = lines[(baseLine->index + n) % lines.size()];

		if (l->index < playerLine->index)
			continue;

		for (unsigned int i = 0; i < l->lineProps.size(); ++i)
		{
			Prop* p = l->lineProps[i];
			l->renderProps(sprites, i);
		}
	}

	//Render layout
	App->renderer->Blit(layout, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
}

void Road::ActivateAnims()
{
	//Activate animations of flagmen and light
	flagman->animLeft.speed = 0.12f;
	flagman->animRight.speed = 0.12f;
	trafficLight->animLeft.speed = 0.063f;
	trafficLight->animRight.speed = 0.063f;
}

void Road::AddFlagmanAnim()
{
	flagman = new Prop();
	flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });
	for (int i = 0; i < 12; ++i)
		flagman->animLeft.frames.push_back({ 83, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 165, 1, 81, 103 });

	flagman->animLeft.frames.push_back({ 247, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 329, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 411, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 493, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 575, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 657, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });

	for (int i = 0; i < 4; ++i)
	{
		flagman->animLeft.frames.push_back({ 739, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 247, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 329, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 411, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 493, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 575, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 657, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });
	}

	for (int i = 0; i < 2; ++i)
	{
		flagman->animLeft.frames.push_back({ 821, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 821, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	}

	flagman->animLeft.frames.push_back({ 247, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 329, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 411, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 493, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 575, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 657, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });

	for (int i = 0; i < 2; ++i)
	{
		flagman->animLeft.frames.push_back({ 739, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 247, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 329, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 411, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 493, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 575, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 657, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });
	}

	for (int i = 0; i < 2; ++i)
	{
		flagman->animLeft.frames.push_back({ 821, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 821, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	}

	flagman->animLeft.frames.push_back({ 247, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 329, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 411, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 493, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 575, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 657, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });

	flagman->animLeft.frames.push_back({ 739, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 247, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 329, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 411, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 493, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 575, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 657, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 1, 1, 81, 103 });

	for (int i = 0; i < 3; ++i)
	{
		flagman->animLeft.frames.push_back({ 821, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 821, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
		flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	}
	flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 903, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 985, 1, 81, 103 });
	flagman->animLeft.frames.push_back({ 1067, 1, 81, 103 });

	flagman->animLeft.speed = 0.f;
	flagman->animLeft.loop = false;
	flagman->pivotL = { 0.58f, 0.91f };
	flagman->pivotR = { 0.58f, 0.91f };
	flagman->animRight = flagman->animLeft;
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
		AddSegment(EaseIn(0, curve, (float)n / enter), EaseInOut(firstY, endY, (float)n / total), mirror, dist);
	}
		
	for (n = 0; n < hold; ++n)
	{
		dist += (int)distPerc;
		AddSegment(curve, EaseInOut(firstY, endY, (float)(enter + n) / total), mirror, dist);
	}
		
	for (n = 0; n < leave; ++n)
	{
		dist += (int)distPerc;
		AddSegment(EaseInOut(curve, 0, (float)n / leave), EaseInOut(firstY, endY, (float)(enter + hold + n) / total), mirror, dist);
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

void Road::AddProp(unsigned int line, Prop* p, float offsetX, float offsetY)
{
	if (line < lines.size())
	{
		lines[line]->lineProps.push_back(p);
		lines[line]->offsetsX.push_back(offsetX);
		lines[line]->offsetsY.push_back(offsetY);
	}
}

void Road::UpdateWheels()
{
	pWheelL = playerX * ROAD_WIDTH - 210;
	pWheelR = playerX * ROAD_WIDTH + 210;

	App->player->wheelR = App->player->wheelL = NORMAL;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT || App->player->speed > 0.f) {
		if (pWheelR < -1831 || pWheelR > roadDistance + 1831)
			App->player->wheelR = SAND;
		if (pWheelL < -1831 || pWheelL > roadDistance + 1831)
			App->player->wheelL = SAND;

		if (roadDistance > 3662)
		{
			if (pWheelR > 1831 && pWheelR < 1831 + (roadDistance - 3662))
				App->player->wheelR = SAND;
			if (pWheelL > 1831 && pWheelL < 1831 + (roadDistance - 3662))
				App->player->wheelL = SAND;
		}
	}
}