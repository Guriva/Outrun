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
	backgroundLvl1 = { 0, 0, 4030, 243 };
	background2Lvl1 = { 810, 243, 1900, 11 };

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
	sign75->collider = true;
	sign75->wCol = 26;
	sign75->pivotColL = { 0.38f, 1.f };
	sign75->pivotColR = { 0.38f, 1.f };

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
	trafficLight->collider = true;
	trafficLight->wCol = 74;

	slow = new Prop();
	slow->animLeft.frames.push_back({ 449, 105, 60, 112 });
	slow->animRight.frames.push_back({ 388, 105, 60, 112 });
	slow->collider = true;
	slow->wCol = 6;
	slow->pivotColL = { 0.1f, 1.f };
	slow->pivotColR = { 0.9f, 1.f };

	curveSlow = new Prop();
	curveSlow->animLeft.frames.push_back({ 510, 105, 60, 112 });
	curveSlow->animRight.frames.push_back({ 572, 105, 60, 112 });
	curveSlow->collider = true;
	curveSlow->wCol = 6;
	curveSlow->pivotColL = { 0.1f, 1.f };
	curveSlow->pivotColR = { 0.9f, 1.f };

	house1 = new Prop();
	house1->animLeft.frames.push_back({ 632, 105, 120, 86 });
	house1->animRight.frames.push_back({ 632, 105, 120, 86 });
	house1->collider = true;
	house1->wCol = 120;

	house2 = new Prop();
	house2->animLeft.frames.push_back({ 753, 105, 120, 86 });
	house2->animRight.frames.push_back({ 753, 105, 120, 86 });
	house2->collider = true;
	house2->wCol = 120;

	house3 = new Prop();
	house3->animLeft.frames.push_back({ 874, 105, 120, 86 });
	house3->animRight.frames.push_back({ 874, 105, 120, 86 });
	house3->collider = true;
	house3->wCol = 120;

	house4 = new Prop();
	house4->animLeft.frames.push_back({ 582, 296, 116, 64 });
	house4->animRight.frames.push_back({ 582, 296, 116, 64 });
	house4->collider = true;
	house4->wCol = 98;
	house4->pivotColL = { 0.42f, 1.f };
	house4->pivotColR = { 0.42f, 1.f };

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
	palm1->collider = true;
	palm1->wCol = 20;
	palm1->pivotColL = { 0.36f, 1.f };
	palm1->pivotColR = { 0.64f, 1.f };

	palm2 = new Prop();
	palm2->animLeft.frames.push_back({ 453, 296, 128, 79 });
	palm2->animRight.frames.push_back({ 453, 296, 128, 79 });
	palm2->collider = true;
	palm2->wCol = 20;

	start = new Prop();
	start->animLeft.frames.push_back({ 1, 234, 472, 61 });
	start->animRight.frames.push_back({ 1, 234, 472, 61 });
	start->pivotL = { 0.f, 1.f };
	start->pivotR = { 1.f, 1.f };

	people1 = new Prop();
	people1->animLeft.frames.push_back({ 474, 230, 188, 65 });
	people1->animRight.frames.push_back({ 474, 230, 188, 65 });
	people1->collider = true;
	people1->wCol = 188;

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
	panel1->collider = true;
	panel1->wCol = 118;

	panel2 = new Prop();
	panel2->animLeft.frames.push_back({ 352, 296, 100, 101 });
	panel2->animRight.frames.push_back({ 352, 296, 100, 101 });
	panel2->collider = true;
	panel2->wCol = 92;

	panel3 = new Prop();
	panel3->animLeft.frames.push_back({ 663, 215, 116, 80 });
	panel3->animRight.frames.push_back({ 663, 215, 116, 80 });
	panel3->collider = true;
	panel3->wCol = 116;

	panel4 = new Prop();
	panel4->animLeft.frames.push_back({ 325, 105, 62, 128 });
	panel4->animRight.frames.push_back({ 325, 105, 62, 128 });
	panel4->scale = 1.2f;
	panel4->collider = true;
	panel4->wCol = 62;

	vulturesign = new Prop();
	vulturesign->animLeft.frames.push_back({ 699, 296, 224, 152 });
	vulturesign->animRight.frames.push_back({ 699, 296, 224, 152 });
	vulturesign->collider = true;
	vulturesign->wCol = 8;
	vulturesign->pivotColL = { 0.98f, 1.f };
	vulturesign->pivotColR = { 0.98f, 1.f };

	active.reserve(6);

	/*truck1->left.frames.push_back({ 1, 1, 50, 55 });
	truck1->left.frames.push_back({ 1, 57, 50, 55});
	truck1->left.speed = 0.5f;
	truck1->right.frames.push_back({ 52, 1, 50, 55});
	truck1->right.frames.push_back({ 52, 57, 50, 55});
	truck1->right.speed = 0.5f;*/
}

Road::~Road()
{}

bool Road::Start()
{
	//Road parameters
	fov = 120.f;
	cameraHeight = 800.f;
	drawDistance = 200;
	segmentL = 150;
	rumbleL = 3.f;
	roadLanes = 3;
	lineW = 20;
	roadDistance = 0;
	offsetXBackground1 = 1000.f;
	offsetXBackground2 = 0.f;

	//Initial position
	cameraDistance = 1 / tan((float)((fov / 2.f) * M_PI / 180.0f));
	playerX = collisionDir = 0.f;
	playerY = 0;
	iniPosition = position = 300 * (int)SEGMENT_LENGTH;
	playerZ = (int)(cameraHeight * cameraDistance) + 241;
	playerW = 77;
	playerRoad = LEFTROAD;
	pWheelL = -210;
	pWheelR = 210;
	thresholdX = 0;

	//Set distances for road lanes
	dist3 = 0;
	dist4 = dist3 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist5 = dist4 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist6 = dist5 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist7 = dist6 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	dist8 = dist7 + ((int)ROAD_WIDTH * 16 / 27) + ((int)ROAD_WIDTH / 18);
	distM = dist8 + ((int)ROAD_WIDTH * 16 / 27) * 7 + ((int)ROAD_WIDTH / 18) * 7;

	return true;
}

// Load assets
bool Road::InitRoad()
{
	LOG("Loading level scene");

	//Load textures
	backgrounds = App->textures->Load("Textures/Level/backgroundlvl1.png");
	layout = App->textures->Load("Textures/Level/layoutLevel.png");
	sprites = App->textures->Load("Textures/Level/spriteslvl1.png");
	cars = App->textures->Load("Textures/Level/cars.png");
	//Create Road
	AddStraight(100, false, dist8);
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
	AddProp(305, woman3, -0.63f, 0.f, false);
	AddProp(305, musicman, -0.3f, 0.f, false);
	AddProp(305, cameraman, -0.5f, 0.f, false);
	AddProp(305, woman1, 0.5f, 0.f, false);

	AddProp(306, man1, -0.7f, 0.f, false);
	AddProp(306, man3, -0.5f, 0.f, false);
	AddProp(306, flagman, -0.3f, 0.f, false);
	AddProp(309, start, -1.25f, -1.8f, false);
	AddProp(309, trafficLight, -0.8f, 0.f, false);
	AddProp(309, panel4, 1.f, 0.f, false);

	float sep = 1;
	/*for (int i = 1; i < 36; i += 3)
	{
		AddProp(i + (int)sep, palm1, -0.8f, 0.f);
		AddProp(i + (int)sep, palm1, 0.8f, 0.f);
		sep *= 1.5f;
	}*/

	for (int i = 1; i < 300; i += 3)
	{
		AddProp(i + (int)sep, palm1, -0.8f, 0.f, false);
		AddProp(i + (int)sep, palm1, 0.8f, 0.f, false);
		AddProp(i + (int)sep, palm1, 0.8f, 0.f, true);
		sep *= 1.3f;
	}

	//AddProp(30, palm1, 0.1f, 0.f);
	//AddProp(60, palm1, 0.1f, 0.f);
	//AddProp(260, palm1, -0.8f, 0.f);
	//AddProp(260, house2, -0.8f, 0.f);

	roadDistance = lines[0]->distance;
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

void Road::UpdateRoad(float time)
{
	UpdateCars();
	CheckCarsState();

	iniPosition = position;
	//Update player position
	position += (int)(App->player->speed);
	while (position >= trackLength)
		position -= trackLength;
	while (position < 0)
		position += trackLength;

	//Calculate playerY for hills
	Line* playerLine = lines[(int)((position + playerZ) / segmentL) % lines.size()];
	float playerPerc = (float)(((position + playerZ) % (int)segmentL) / segmentL);
	playerY = (int)(playerLine->p1.yWorld + (playerLine->p2.yWorld - playerLine->p1.yWorld) * playerPerc);
	Line* l;

	if (App->player->playerState == ONROAD)
	{
		varThresholdX = (App->player->speed / App->player->maxSpeed) * 2.5f;
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (thresholdX > -varThresholdX)
			{
				thresholdX -= 0.15f;
				if (thresholdX < -varThresholdX)
					thresholdX = -varThresholdX;
			}
		}
		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (thresholdX < varThresholdX)
			{
				thresholdX += 0.15f;
				if (thresholdX > varThresholdX)
					thresholdX = varThresholdX;
			}
		}
		else
		{
			if (thresholdX != 0.f)
			{
				thresholdX -= thresholdX * 0.1f;
				if (thresholdX < 0.1f && thresholdX > -0.1f)
					thresholdX = 0.f;
			}
		}

		playerX += (thresholdX * time);

		CheckPlayerCollision(playerLine);
	}
	else
	{
		if (collisionDir >= 0)
			playerX -= (App->player->speed / App->player->maxSpeed) * 2 * time;
		else
			playerX += (App->player->speed / App->player->maxSpeed) * 2 * time;

		Animation* anim = App->player->current_animation;

		if (anim->Finished())
		{
			if (playerX < -0.05f)
				playerX += 0.012f;
			else if (playerX > 0.05f)
				playerX -= 0.012f;
			else
			{
				anim->Reset();
				anim->ResetLoops();
				App->player->lowAccel = App->player->maxSpeed / 6.5f;
				App->player->speed = 0.f;
				App->player->playerState = ONROAD;
				App->player->resetCounters();
			}
		}
	}

	playerRoad = (abs(playerLine->p1.xCamera) <= abs(playerLine->p11.xCamera) ? LEFTROAD : RIGHTROAD);
	
	//Apply centrifugal to curves
	float centrifugal = (App->player->speed > 26 ? 0.5f : 0.f);
	if (App->player->speed >= 100)
		centrifugal = (App->player->speed - 50.f) / 100.f;
	switch (playerRoad)
	{
	case RIGHTROAD:
		if (roadDistance != playerLine->distance)
			playerX += (playerLine->distance - roadDistance) / (float)ROAD_WIDTH;
		if (playerLine->mirror)
			playerX += (playerLine->curve * MIN((App->player->speed / App->player->maxSpeed),1.f) * centrifugal * time);
		else
			playerX -= (playerLine->curve * MIN((App->player->speed / App->player->maxSpeed),1.f) * centrifugal * time);
		break;
	case LEFTROAD:
		playerX -= (playerLine->curve * MIN((App->player->speed / App->player->maxSpeed),1.f) * centrifugal * time);
		break;
	}
		

	roadDistance = (int)playerLine->distance;

	UpdateWheels();

	//Later update speed when both wheels are in sand
	if (App->player->wheelL == SAND && App->player->wheelR == SAND)
		App->player->maxSpeed = 50.f;
	else
	{
		if (App->player->gear)
			App->player->maxSpeed = (int)SEGMENT_LENGTH;
		else
			App->player->maxSpeed = 100.f;
	}
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

void Road::AddProp(unsigned int line, Prop* p, float offsetX, float offsetY, bool side)
{
	if (line < lines.size())
	{
		lines[line]->lineProps.push_back(p);
		lines[line]->offsetsX.push_back(offsetX);
		lines[line]->offsetsY.push_back(offsetY);
		lines[line]->sides.push_back(side);
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

void Road::UpdateCars()
{

}

void Road::CheckCarsState()
{

}

void Road::CheckPlayerCollision(const Line* playerLine)
{
	for (unsigned int n = 0; n < playerLine->lineProps.size(); ++n)
	{
		Prop* p = playerLine->lineProps[n];

		if (p->collider && App->player->playerState == ONROAD)
		{
			PointLine point = playerLine->p1;
			if (playerLine->sides[n])
				point = playerLine->p11;

			float x2 = point.xScreen + (playerLine->offsetsX[n] * point.scale * ROAD_WIDTH * SCREEN_WIDTH / 2);
			float scale = 1.6f * (0.3f * (1.f / 170.f)) * point.scale * SCREEN_WIDTH * ROAD_WIDTH * p->scale;
			if (playerLine->offsetsX[n] >= 0)
				x2 = x2 + p->animRight.GetCurrentFrame().w * scale * p->pivotColR.x;
			
			else
				x2 = x2 - p->animLeft.GetCurrentFrame().w * scale * (1 - p->pivotColL.x);
			
			if (Collides((int)(SCREEN_WIDTH / 2) + 5, playerW, x2, p->wCol, scale))
			{
				collisionDir = playerX;
				float speed = App->player->speed;
				if (speed < 80) {
					App->player->current_animation = &(App->player->crash1);
					App->player->playerState = SMALLCOLLISION;
				}
				
				else if (speed >= 80 && speed <= 150) {
					App->player->current_animation = &(App->player->crash2);
					//Collision animation time to stop at 0.8 (1 turn)
					App->player->lowAccel = (speed / 0.8f);
					App->player->playerState = MEDIUMCOLLISION;
				}
				else if (speed > 150 && speed <= 190) {
					App->player->current_animation = &(App->player->crash21);
					//Collision animation time to stop at 1.6 (2 turns)
					App->player->lowAccel = (speed / 1.6f);
					App->player->playerState = MEDIUMCOLLISION;
				}
			}
		}
	}
}

bool Road::Collides(float x1, int w1, float x2, float w2, float scale)
{
	//Player offsetX at 0.5
	float min1 = x1 - (((float)w1*3.2f) / 2.f);
	float max1 = x1 + (((float)w1*3.2f) / 2.f);

	float min2 = x2 - ((w2*scale) / 2.f);
	float max2 = x2 + ((w2*scale) / 2.f);

	App->renderer->DrawQuad({ (int)min1, 60, (int)(max1 - min1), 90 }, 255, 0, 0, 255, false);

	//return false;
	return (max1 >= min2 && max2 >= min1);
}

void Road::DrawRoad()
{
	Line* playerLine = lines[(int)((position + playerZ) / segmentL) % lines.size()];
	Line* baseLine = lines[(int)(position / segmentL) % lines.size()];
	float percent = (float)((position % (int)segmentL) / segmentL);
	float difX = -(baseLine->curve * percent);
	float sumX = 0;
	Line* l;

	playerLine->projection(playerLine->p1, (int)((playerX * ROAD_WIDTH) - sumX), (int)((float)cameraHeight + playerY), position, cameraDistance);
	float maxY = playerLine->p1.yScreen;

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

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18) * 2 + (w1 * 16 / 27), y1, x1 + w1 - (w1 / 18) * 2 - (w1 * 16 / 27), y1, x2 + w2 - (w2 / 18) * 2 - (w2 * 16 / 27), y2, x2 - w2 + (w2 / 18) * 2 + (w2 * 16 / 27), y2, road);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18) * 2 + (w11 * 16 / 27), y11, x11 + w11 - (w11 / 18) * 2 - (w11 * 16 / 27), y11, x21 + w21 - (w21 / 18) * 2 - (w21 * 16 / 27), y21, x21 - w21 + (w21 / 18) * 2 + (w21 * 16 / 27), y21, road);

		maxY = l->p2.yScreen;
	}

	//Render sky background
	App->renderer->DrawQuad({ 0, 0, SCREEN_WIDTH, (int)maxY + SCREEN_Y_OFFSET }, 0, 148, 255, 255);

	//Render second background
	//El background depen del valor de la curva!! (Si la corba es positiva, el valor en X disminueix. Si el valor en X baixa del limit, pasar al valor màxim. El mateix per quan corba negativa)
	//El valor en Y depen del maxY;
	if (!playerLine->mirror)
		offsetXBackground1 += playerLine->curve * (position - iniPosition) / SEGMENT_LENGTH * 2.f;
	if (offsetXBackground1 + SCREEN_WIDTH > backgroundLvl1.w)
		offsetXBackground1 = 0.f;
	if (offsetXBackground1 < 0.f)
		offsetXBackground1 = backgroundLvl1.w - SCREEN_WIDTH;

	float destX = backgroundLvl1.x + offsetXBackground1;
	float destY = MAX(backgroundLvl1.y, backgroundLvl1.y + (backgroundLvl1.h - (maxY + SCREEN_Y_OFFSET)));
	float destW = SCREEN_WIDTH;
	float destH = MIN(backgroundLvl1.h, (maxY + SCREEN_Y_OFFSET));
	SDL_Rect dest = { destX, destY, destW, destH };
	App->renderer->Blit(backgrounds, 0, maxY + SCREEN_Y_OFFSET, &dest, 1.f, { 1.f, 1.f }, { 0.f, 1.f });

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