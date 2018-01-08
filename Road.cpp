#include "Application.h"
#include "Road.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "Line.h"
#include "Globals.h"
#include "Util.h"
#include <cstdlib>
#include <algorithm>

using namespace std;

Road::Road()
{
	srand((unsigned int)time(NULL));

	backgroundLvl1 = { 0, 0, 4030, 243 };

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
	sign75->scale = 1.5f;
	sign75->collider = true;
	sign75->wCol = 26;
	sign75->pivotColL = { 0.38f, 1.f };
	sign75->pivotColR = { 0.38f, 1.f };

	trafficLight = new Prop();
	trafficLight->animLeft.frames.push_back({ 250, 105, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 127, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 202, 296, 74, 128 });
	trafficLight->animLeft.frames.push_back({ 277, 296, 74 ,128 });
	trafficLight->animLeft.frames.push_back({ 277, 296, 74 ,128 });
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
	water->animRight.frames.push_back({ 1, 169, 244, 32 });

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

	desertSand = new Prop();
	desertSand->animLeft.frames.push_back({ 453, 376, 244, 32 });
	desertSand->animRight.frames.push_back({ 453, 409, 244, 32 });

	nomad = new Prop();
	nomad->animLeft.frames.push_back({ 416, 398, 36, 63 });
	nomad->animRight.frames.push_back({ 416, 398, 36, 63 });

	camel1 = new Prop();
	camel1->animLeft.frames.push_back({ 453, 477, 36, 34 });
	camel1->animRight.frames.push_back({ 453, 442, 36, 34 });
	camel1->scale = 1.4f;

	camel2 = new Prop();
	camel2->animLeft.frames.push_back({ 490, 442, 42, 27 });
	camel2->animRight.frames.push_back({ 490, 470, 42, 27 });
	camel2->scale = 1.4f;

	camel3 = new Prop();
	camel3->animLeft.frames.push_back({ 533, 483, 57, 40 });
	camel3->animRight.frames.push_back({ 533, 442, 57, 40 });
	camel3->scale = 1.4f;

	log = new Prop();
	log->animLeft.frames.push_back({ 1109, 358, 28, 192 });
	log->animRight.frames.push_back({ 1109, 358, 28, 192 });

	end = new Prop();
	end->animLeft.frames.push_back({ 605, 528, 472, 62 });
	end->animRight.frames.push_back({ 605, 528, 472, 62 });
	end->pivotL = { 0.f, 1.f };
	end->pivotR = { 1.f, 1.f };

	checkpoint = new Prop();
	checkpoint->animLeft.frames.push_back({ 1, 489, 218, 154 });
	checkpoint->animRight.frames.push_back({ 220, 489, 218, 154 });
	checkpoint->scale = 1.2f;
	checkpoint->collider = true;
	checkpoint->wCol = 14;
	checkpoint->pivotColL = { 0.064f, 1.f };
	checkpoint->pivotColR = { 0.936f, 1.f };


	active.reserve(6);

	truck1 = new Car();
	truck1->left.frames.push_back({ 1, 1, 50, 55 });
	truck1->left.frames.push_back({ 1, 57, 50, 55 });
	truck1->left.speed = 0.2f;
	truck1->right.frames.push_back({ 52, 1, 50, 55 });
	truck1->right.frames.push_back({ 52, 57, 50, 55 });
	truck1->right.speed = 0.2f;
	truck1->active = false;
	truck1->speed = 120.f;
	truck1->current_anim = &truck1->left;
	truck1->offset = 0.5f;
	truck1->side = true;
	truck1->zPos = 190.f*SEGMENT_LENGTH;
	active.push_back(truck1);

	truck2 = new Car();
	truck2->left.frames.push_back({ 103, 1, 50, 55 });
	truck2->left.frames.push_back({ 103, 57, 50, 55 });
	truck2->left.speed = 0.2f;
	truck2->right.frames.push_back({ 154, 1, 50, 55 });
	truck2->right.frames.push_back({ 154, 57, 50, 55 });
	truck2->right.speed = 0.2f;
	truck2->active = false;
	truck2->speed = 120.f;
	truck2->current_anim = &truck2->left;
	truck2->offset = 0.f;
	truck2->side = true;
	truck2->zPos = 170.f*SEGMENT_LENGTH;
	active.push_back(truck2);

	atom1 = new Car();
	atom1->left.frames.push_back({ 1, 113, 51, 31 });
	atom1->left.frames.push_back({ 1, 145, 51, 31 });
	atom1->left.speed = 0.2f;
	atom1->right.frames.push_back({ 53, 113, 51, 31 });
	atom1->right.frames.push_back({ 53, 145, 51, 31 });
	atom1->right.speed = 0.2f;
	atom1->active = false;
	atom1->speed = 120.f;
	atom1->current_anim = &atom1->left;
	atom1->offset = 0.5f;
	atom1->side = true;
	atom1->zPos = 165.f*SEGMENT_LENGTH;
	active.push_back(atom1);

	atom2 = new Car();
	atom2->left.frames.push_back({ 105, 113, 51, 31 });
	atom2->left.frames.push_back({ 105, 145, 51, 31 });
	atom2->left.speed = 0.2f;
	atom2->right.frames.push_back({ 157, 113, 51, 31 });
	atom2->right.frames.push_back({ 157, 145, 51, 31 });
	atom2->right.speed = 0.2f;
	atom2->active = false;
	atom2->speed = 120.f;
	atom2->current_anim = &atom2->left;
	atom2->offset = -0.5f;
	atom2->side = true;
	atom2->zPos = 160.f*SEGMENT_LENGTH;
	active.push_back(atom2);

	out1 = new Car();
	out1->left.frames.push_back({ 1, 177, 45, 35 });
	out1->left.frames.push_back({ 1, 213, 45, 35 });
	out1->left.speed = 0.2f;
	out1->right.frames.push_back({ 47, 177, 45, 35 });
	out1->right.frames.push_back({ 47, 213, 45, 35 });
	out1->right.speed = 0.2f;
	out1->active = false;
	out1->speed = 120.f;
	out1->current_anim = &out1->left;
	out1->offset = 0.5f;
	out1->side = true;
	out1->zPos = 155.f*SEGMENT_LENGTH;
	active.push_back(out1);

	out2 = new Car();
	out2->left.frames.push_back({ 93, 177, 45, 35 });
	out2->left.frames.push_back({ 93, 213, 45, 35 });
	out2->left.speed = 0.2f;
	out2->right.frames.push_back({ 139, 177, 45, 35 });
	out2->right.frames.push_back({ 139, 213, 45, 35 });
	out2->right.speed = 0.2f;
	out2->active = false;
	out2->speed = 120.f;
	out2->current_anim = &out2->left;
	out2->offset = 0.f;
	out2->side = true;
	out2->zPos = 150.f*SEGMENT_LENGTH;
	active.push_back(out2);
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
	swapping = false;
	backgroundSwapOffset = 0.f;
	ending = false;
	sameColors = 0;

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
	distM = dist8 + ((int)ROAD_WIDTH * 16 / 27) * 10 + ((int)ROAD_WIDTH / 18) * 10;

	return true;
}

// Load assets
bool Road::InitRoad()
{
	//LOG("Loading road");

	//Load textures
	background1 = App->textures->Load("Textures/Level/backgroundlvl1.png");
	background2 = nullptr;
	sprites = App->textures->Load("Textures/Level/spriteslvl1.png");
	cars = App->textures->Load("Textures/Level/cars.png");

	//Create Road
	beach = new Biome();
	end1 = new Biome();

	beach->left = end1;
	beach->right = end1;
	beach->b1 = { 148, 255, 255, 255 };
	beach->c1 = { 230, 214, 197, 255 };
	beach->c11 = { 239, 222, 206, 255 };
	beach->c2 = { 156, 156, 156, 255 };
	beach->c21 = { 148, 148, 148, 255 };
	beach->c3 = { 247, 247, 247, 255 };
	beach->c31 = { 148, 148, 148, 255 };
	beach->c4 = { 156, 156, 156, 255 };
	beach->c41 = { 247, 247, 247, 255 };
	beach->background = App->textures->Load("Textures/Level/backgroundlvl1.png");

	end1->end = true;
	end1->b1 = { 239, 235, 222, 255 };
	end1->c1 = { 255, 235, 221, 255 };
	end1->c11 = { 251, 229, 215, 255 };
	end1->c2 = { 156, 156, 156, 255 };
	end1->c21 = { 148, 148, 148, 255 };
	end1->c3 = { 247, 247, 247, 255 };
	end1->c31 = { 148, 148, 148, 255 };
	end1->c4 = { 156, 156, 156, 255 };
	end1->c41 = { 247, 247, 247, 255 };
	end1->background = App->textures->Load("Textures/Level/background2lvl1.png");
	actual = beach;

	bg = beach->b1;
	sand = beach->c1; sand2 = beach->c11; road = beach->c2; road2 = beach->c21;
	rumble = beach->c3; rumble2 = beach->c31; lane = beach->c4; lane2 = beach->c41;

	//beach road
	AddStraight(100, false, dist8, beach);
	AddStraight(20, false, dist8, beach);
	AddHill(10, -5, dist8, 1, beach);
	AddHill(5, 60, dist7, 28, beach);
	AddCurve(100, -1.5, false, dist7, 2, beach);
	AddStraight(26, false, dist7, beach);
	AddRoad(50, 50, 0, 1.5, 0, false, dist7, beach);
	AddRoad(0, 100, 0, 1.5, 20, false, dist7, beach);
	AddRoad(0, 50, 100, 1.5, -10, false, dist7, beach);
	AddHill(40, 20, dist6, 1, beach);
	AddRoad(30, 60, 0, 0, -15, false, dist6, beach);
	AddRoad(0, 170, 85, -1.5, 0, false, dist6, beach);
	AddStraight(50, false, dist6, beach);
	AddCurve(60, -3, false, dist6, 2, beach);
	AddStraight(70, false, dist6, beach);
	AddCurve(20, 3, false, dist6, 8, beach);
	AddHill(25, -10, dist6, 2, beach);
	AddRoad(20, 40, 0, -3, 10, false, dist6, beach);
	AddRoad(0, 80, 0, -3, -5, false, dist6, beach);
	AddRoad(0, 70, 0, -3, 15, false, dist6, beach);
	AddRoad(0, 50, 20, -3, 0, false, dist6, beach);
	AddStraight(100, false, dist6, beach);
	AddCurve(30, -3, false, dist6, 2, beach);
	AddStraight(30, false, dist6, beach);
	AddStraight(30, false, dist5, beach);
	AddCurve(20, -3.5, false, dist5, 3, beach);
	AddRoad(10, 60, 10, 3.5, 20, false, dist5, beach);
	AddRoad(10, 90, 10, -3.5, 25, false, dist4, beach);
	AddStraight(10, false, dist4, beach);
	AddStraight(50, false, dist3, beach);
	AddHill(10, 5, dist3, 2, beach);
	AddHill(10, -5, dist3, 2, beach);
	AddHill(10, 5, dist3, 2, beach);
	AddRoad(10, 400, 50, -2, 0, true, dist3, beach);
	AddStraight(100, true, distM, beach);

	//end1 road
	AddStraight(400, false, dist3, end1);

	//Beach props
	AddProp(305, woman3, -0.63f, 0.f, false, beach);
	AddProp(305, musicman, -0.3f, 0.f, false, beach);
	AddProp(305, cameraman, -0.5f, 0.f, false, beach);
	AddProp(305, woman1, 0.5f, 0.f, false, beach);

	AddProp(306, man1, -0.7f, 0.f, false, beach);
	AddProp(306, man3, -0.5f, 0.f, false, beach);
	AddProp(306, flagman, -0.3f, 0.f, false, beach);
	AddProp(309, start, -1.25f, -1.8f, false, beach);
	AddProp(309, trafficLight, -0.8f, 0.f, false, beach);
	AddProp(309, panel4, 1.f, 0.f, false, beach);

	unsigned int i;

	for (i = 300; i < 360; i += 2)
	{
		AddProp(i, people1, -1.2f, 0.f, false, beach);
	}

	float sep = 1.0f;
	for (i = 299; i < 350; i += 3)
	{
		AddProp(i + (int)sep, palm1, -0.8f, 0.f, false, beach);
		AddProp(i + (int)sep, palm1, 0.8f, 0.f, false, beach);
		sep *= 1.1f;
	}

	for (i = 450; i < 550; i += 2)
	{
		AddProp(i, people1, -1.2f, 0.f, false, beach);
	}

	for (i = 0; i < 10; ++i)
	{
		for (unsigned int j = 530; j < 554; j += 8)
		{
			if (i % 3 == 0)
				AddProp(j + i * 90, sign75, 1.2f, 0.f, false, beach);
			else
				AddProp(j + i * 90, palm2, 1.f, 0.f, false, beach);
		}
	}

	for (i = 550; i < 1600; i += 10)
	{
		AddProp(i, palm1, -0.8f, 0.f, false, beach);
		AddProp(i, palm1, 0.8f, 0.f, true, beach);
	}

	for (i = 1620; i < 1850; i += 15)
	{
		AddProp(i, palm2, -1.f, 0.f, false, beach);
		AddProp(i, palm2, 1.f, 0.f, true, beach);
		AddProp(i + 5, palm2, -1.6f, 0.f, false, beach);
		AddProp(i + 5, palm2, 1.6f, 0.f, true, beach);
	}

	for (i = 1902; i < 3150; i += 2)
	{
		AddProp(i, water, -6.5f, 0.f, false, beach);
		AddProp(i, water, -5.5f, 0.f, false, beach);
		AddProp(i, water, -4.5f, 0.f, false, beach);
		AddProp(i, water, -3.5f, 0.f, false, beach);
		AddProp(i, water, -2.5f, 0.f, false, beach);
		AddProp(i, water, -1.5f, 0.f, false, beach);
		if (i % 50 == 0)
		{
			AddProp(i, surf1, -2.5f, 0.f, false, beach);
			AddProp(i - 10, surf2, -3.f, 0.f, false, beach);
			AddProp(i - 15, surf3, -3.5f, 0.f, false, beach);
			AddProp(i, palm1, 0.8f, 0.f, true, beach);
			AddProp(i - 10, palm1, 1.3f, 0.f, true, beach);
			AddProp(i - 15, palm1, 1.f, 0.f, true, beach);
		}
	}
	AddProp(2250, checkpoint, -0.8f, 0.f, false, beach);
	AddProp(2250, checkpoint, 0.8f, 0.f, true, beach);

	for (i = 1930; i < 1990; i += 15)
		AddProp(i, slow, 1.2f, 0.f, true, beach);
	for (i = 2000; i < 2100; i += 25)
		AddProp(i, panel3, 1.f, 0.f, true, beach);
	for (i = 2400; i < 2460; i += 15)
		AddProp(i, slow, -1.2f, 0.f, false, beach);
	for (i = 2700; i < 2760; i += 15)
		AddProp(i, slow, 1.2f, 0.f, true, beach);
	for (i = 3100; i < 3200; i += 25)
		AddProp(i, panel3, 1.f, 0.f, true, beach);
	AddProp(3250, slow, 1.2f, 0.f, true, beach);

	for (i = 3300; i < 3800; i += 2)
	{
		if (i % 50 == 0)
		{
			AddProp(i, palm1, 0.8f, 0.f, true, beach);
			AddProp(i - 10, palm1, 1.3f, 0.f, true, beach);
			AddProp(i - 15, palm1, 1.f, 0.f, true, beach);
			AddProp(i + 10, palm1, -0.8f, 0.f, false, beach);
			AddProp(i, palm1, -1.3f, 0.f, false, beach);
			AddProp(i - 5, palm1, -1.f, 0.f, false, beach);
		}
		if (i % 60 == 0)
		{
			AddProp(i, house1, -1.f, 0.f, false, beach);
			AddProp(i + 10, house2, -1.f, 0.f, false, beach);
			AddProp(i + 20, house1, -1.f, 0.f, false, beach);
			AddProp(i, house2, 1.f, 0.f, true, beach);
			AddProp(i + 20, house3, 1.f, 0.f, true, beach);
			AddProp(i + 35, house1, 1.f, 0.f, true, beach);
		}
	}
	AddProp(3450, house4, 1.f, 0.f, true, beach);
	for (i = 3460; i < 3540; i += 20)
		AddProp(i, panel1, -1.f, 0.f, false, beach);
	for (i = 3540; i < 3600; i += 20)
		AddProp(i, panel2, 1.f, 0.f, true, beach);
	AddProp(3600, slow, 1.f, 0.f, true, beach);
	AddProp(3610, slow, 1.f, 0.f, true, beach);
	AddProp(3620, slow, 1.f, 0.f, true, beach);
	AddProp(3640, panel1, -1.f, 0.f, false, beach);
	AddProp(3650, panel1, -1.f, 0.f, false, beach);
	AddProp(3660, curveSlow, 1.f, 0.f, true, beach);
	AddProp(3670, curveSlow, 1.f, 0.f, true, beach);
	AddProp(3680, curveSlow, 1.f, 0.f, true, beach);
	for (i = 3815; i < 3900; i += 15)
	{
		AddProp(i, palm2, -1.f, 0.f, false, beach);
		AddProp(i, palm2, 1.f, 0.f, true, beach);
		AddProp(i + 5, palm2, -1.6f, 0.f, false, beach);
		AddProp(i + 5, palm2, 1.6f, 0.f, true, beach);
	}
	for (i = 3920; i < 4120; i += 2)
	{
		if (i % 50 == 0)
		{
			AddProp(i, palm1, 0.8f, 0.f, true, beach);
			AddProp(i - 10, palm1, 1.3f, 0.f, true, beach);
			AddProp(i - 15, palm1, 1.f, 0.f, true, beach);
			AddProp(i + 10, palm1, -0.8f, 0.f, false, beach);
			AddProp(i, palm1, -1.3f, 0.f, false, beach);
			AddProp(i - 5, palm1, -1.f, 0.f, false, beach);
		}
		if (i % 60 == 0)
		{
			AddProp(i, house1, -1.f, 0.f, false, beach);
			AddProp(i + 10, house2, -1.f, 0.f, false, beach);
			AddProp(i + 20, house1, -1.f, 0.f, false, beach);
			AddProp(i, house2, 1.f, 0.f, true, beach);
			AddProp(i + 20, house3, 1.f, 0.f, true, beach);
			AddProp(i + 35, house1, 1.f, 0.f, true, beach);
		}
	}
	AddProp(4125, vulturesign, 0.1f, 0.f, true, beach);

	//End1 props
	AddProp(705, end, -1.35f, -1.6f, false, end1);
	AddProp(705, log, -1.2f, 0.f, false, end1);
	AddProp(705, log, 1.2f, 0.f, false, end1);
	AddProp(799, nomad, 0.5f, 0.f, false, end1);
	AddProp(800, camel1, -0.2f, 0.f, false, end1);
	AddProp(802, camel1, 0.5f, 0.f, false, end1);
	AddProp(803, camel3, 0.f, 0.f, false, end1);
	AddProp(805, camel2, 0.25f, 0.f, false, end1);
	AddProp(805, end, -1.35f, -1.6f, false, end1);
	AddProp(805, log, -1.2f, 0.f, false, end1);
	AddProp(805, log, 1.2f, 0.f, false, end1);
	for (i = 300; i < 1100; i += 10)
	{
		AddProp(i, desertSand, -6.5f, 0.f, false, end1);
		AddProp(i, desertSand, -5.5f, 0.f, false, end1);
		AddProp(i, desertSand, -4.5f, 0.f, false, end1);
		AddProp(i, desertSand, -3.5f, 0.f, false, end1);
		AddProp(i, desertSand, -2.5f, 0.f, false, end1);
		AddProp(i, desertSand, -1.5f, 0.f, false, end1);
		AddProp(i, desertSand, 6.5f, 0.f, true, end1);
		AddProp(i, desertSand, 5.5f, 0.f, true, end1);
		AddProp(i, desertSand, 4.5f, 0.f, true, end1);
		AddProp(i, desertSand, 3.5f, 0.f, true, end1);
		AddProp(i, desertSand, 2.5f, 0.f, true, end1);
		AddProp(i, desertSand, 1.5f, 0.f, true, end1);
	}


	roadDistance = (int)actual->lines[0]->distance;
	trackLength = (int)(actual->lines.size() * segmentL);

	return true;
}

// UnLoad assets
bool Road::CleanUp()
{
	//LOG("Unloading level scene");
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
	RELEASE(desertSand);
	RELEASE(nomad);
	RELEASE(camel1);
	RELEASE(camel2);
	RELEASE(camel3);
	RELEASE(log);
	RELEASE(end);
	RELEASE(checkpoint);
	RELEASE(truck1);
	RELEASE(truck2);
	RELEASE(atom1);
	RELEASE(atom2);
	RELEASE(out1);
	RELEASE(out2);

	for (unsigned int i = 0; i < beach->lines.size(); ++i)
	{
		RELEASE(beach->lines[i]);
	}
	RELEASE(beach);
	for (unsigned int i = 0; i < end1->lines.size(); ++i)
	{
		RELEASE(end1->lines[i]);
	}
	RELEASE(end1);

	return true;
}

void Road::UpdateRoad(float time)
{
	UpdateCars(time);

	iniPosition = position;
	//Update player position
	position += (int)(App->player->speed);
	while (position >= trackLength)
		position -= trackLength;
	while (position < 0)
		position += trackLength;

	//Calculate playerY for hills
	Line* playerLine = actual->lines[(int)((position + playerZ) / segmentL) % actual->lines.size()];
	float playerPerc = (float)(((position + playerZ) % (int)segmentL) / segmentL);
	playerY = (int)(playerLine->p1.yWorld + (playerLine->p2.yWorld - playerLine->p1.yWorld) * playerPerc);

	//Check for biome road change
	if (App->player->playerState == ONROAD && !actual->end && playerLine->index > actual->lastLine)
	{
		if (playerRoad == LEFTROAD)
			actual = actual->left;
		else
			actual = actual->right;
		if (actual->end) {
			ending = true;
			App->player->playerState = AUTO; //player accelerates to the max speed
		}
		for (unsigned int i = 0; i < active.size(); ++i)
		{
			active[i]->zPos -= position;
			//Cars on the other road will be moved away
			if (active[i]->active && ((playerRoad == LEFTROAD && active[i]->side) || (playerRoad == RIGHTROAD && !active[i]->side)))
			{
				active[i]->zPos += (rand() % (680) + 220)*SEGMENT_LENGTH;
				active[i]->active = false;
				active[i]->side = rand() % 2;
				active[i]->speed = 0.f;
			}
		}

		position = iniPosition = 0;
		trackLength = (int)(actual->lines.size() * segmentL);
		playerY = 0;
	}

	//Check for biome colors change
	if (!actual->biomeSwap && !actual->end && !swapping && playerLine->index > actual->swapLine)
	{
		swapping = true;
		Biome* biome = actual->left;
		if (playerRoad == RIGHTROAD)
			biome = actual->right;

		background2 = biome->background;
		bg2 = biome->b1;
		sandAux = biome->c1; sand2Aux = biome->c11; roadAux = biome->c2; road2Aux = biome->c21;
		rumbleAux = biome->c3; rumble2Aux = biome->c31; laneAux = biome->c4; lane2Aux = biome->c41;
	}

	if (App->player->playerState == ONROAD)
	{
		varThresholdX = App->player->speed * time;
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (thresholdX > -varThresholdX)
				thresholdX -= 0.15f;
			else if (thresholdX < -varThresholdX)
				thresholdX += 0.15f;

		}
		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (thresholdX < varThresholdX)
				thresholdX += 0.15f;
			else if (thresholdX > varThresholdX)
				thresholdX -= 0.15f;
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
	else if (App->player->playerState == SMALLCOLLISION || App->player->playerState == MEDIUMCOLLISION)
	{
		if (collisionDir >= 0)
			playerX -= MIN((App->player->speed / App->player->maxSpeed), 1.f) * 2 * time;
		else
			playerX += MIN((App->player->speed / App->player->maxSpeed), 1.f) * 2 * time;

		Animation* anim = App->player->current_animation;

		if (anim->Finished())
		{
			float dif = 0.f;
			if (playerRoad == RIGHTROAD)
				dif = ((float)roadDistance / (float)ROAD_WIDTH);
			if (playerX < -0.05f + dif)
				playerX += 0.012f;
			else if (playerX > 0.05f + dif)
				playerX -= 0.012f;
			else
			{
				anim->Reset();
				anim->ResetLoops();
				thresholdX = 0.f;
				App->player->lowAccel = 100.f / 6.5f;
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
		//Displacement when player is in right road, and roads are changing distance between them
		if (roadDistance != playerLine->distance)
			playerX += (playerLine->distance - roadDistance) / (float)ROAD_WIDTH;
		if (playerLine->mirror)
			playerX += (playerLine->curve * MIN((App->player->speed / App->player->maxSpeed), 1.f) * centrifugal * time);
		else
			playerX -= (playerLine->curve * MIN((App->player->speed / App->player->maxSpeed), 1.f) * centrifugal * time);
		break;
	case LEFTROAD:
		playerX -= (playerLine->curve * MIN((App->player->speed / App->player->maxSpeed), 1.f) * centrifugal * time);
		break;
	}

	roadDistance = (int)playerLine->distance;

	//Check road limits for player
	if (playerX < -1.5f)
		playerX = -1.48f;
	else if (playerX > 1.5f + ((float)roadDistance / (float)ROAD_WIDTH))
		playerX = 1.48f + ((float)roadDistance / (float)ROAD_WIDTH);

	if (playerLine->mirror)
	{
		if ((float)roadDistance / (float)ROAD_WIDTH > 3.5f && playerX > 1.75f && playerX < (float)roadDistance / (float)ROAD_WIDTH - 1.75f)
		{
			if (playerRoad == LEFTROAD)
				playerX = 1.73f;
			else
				playerX = (float)roadDistance / (float)ROAD_WIDTH - 1.73f;
		}
	}

	//check for checkpoints
	for (unsigned int i = 0; i < playerLine->lineProps.size(); ++i)
	{
		//If checkpoint not visited
		if (playerLine->lineProps[i] == checkpoint && !(find(checkpointsSeen.begin(), checkpointsSeen.end(), playerLine->index) != checkpointsSeen.end()))
		{
			App->ui->checkpoint = true;
			App->ui->timeLeft += 44.f;
			checkpointsSeen.push_back(playerLine->index);
		}
	}

	UpdateWheels();

	//Make smoke if sliding to the side when in a huge curve
	if (App->player->playerState == ONROAD && App->player->wheelL != SAND && App->player->wheelR != SAND && App->player->speed > 100.f)
	{
		if (abs(thresholdX) >= (App->player->speed * time * 0.8f) && abs(playerLine->curve) > 2.5f)
		{
			App->player->wheelL = SMOKE;
			App->player->wheelR = SMOKE;
		}
	}
}

void Road::UpdateRoadEnding(float time)
{
	iniPosition = position;
	//Update player position
	position += (int)(App->player->speed);
	while (position >= trackLength)
		position -= trackLength;
	while (position < 0)
		position += trackLength;

	//Calculate playerY for hills
	Line* playerLine = actual->lines[(int)((position + playerZ) / segmentL) % actual->lines.size()];
	float playerPerc = (float)(((position + playerZ) % (int)segmentL) / segmentL);
	playerY = (int)(playerLine->p1.yWorld + (playerLine->p2.yWorld - playerLine->p1.yWorld) * playerPerc);

	//Keep player on center of road
	if (playerX > 0.1f)
		playerX -= 1.f*time;
	if (playerX < -0.1f)
		playerX += 1.f*time;
	if (playerX != 0.f && playerX < 0.1f && playerX > -0.1f)
		playerX = 0.f;

	//Activate end sequence
	if (playerLine->index == 700)
		App->player->playerState = ENDING;

	playerRoad = (abs(playerLine->p1.xCamera) <= abs(playerLine->p11.xCamera) ? LEFTROAD : RIGHTROAD);
	if (playerRoad == RIGHTROAD && roadDistance != playerLine->distance)
		playerX += (playerLine->distance - roadDistance) / (float)ROAD_WIDTH;

	roadDistance = (int)playerLine->distance;

	//Move cars to the sides, and move to the back those out of range
	for (unsigned int i = 0; i < active.size(); ++i)
	{
		Car* c = active[i];
		if (c->speed > 0.f) c->speed -= 1.f;
		if (c->offset > -0.5f && c->offset <= 0.f) c->offset -= 0.005f;
		if (c->offset < 0.5f && c->offset >= 0.f) c->offset += 0.005f;
		c->zPos += c->speed;
		Line* l = actual->lines[(int)((c->zPos) / segmentL) % actual->lines.size()];
		Line* playerLine = actual->lines[(int)((position + playerZ) / segmentL) % actual->lines.size()];

		if (c->active && (l->index > playerLine->index + drawDistance || l->index < playerLine->index))
			c->active = false;

		float posCar = (c->side ? c->offset * ROAD_WIDTH + roadDistance : c->offset * ROAD_WIDTH);
		if (posCar > playerX * ROAD_WIDTH)
			c->current_anim = &c->left;
		else
			c->current_anim = &c->right;
	}
}

void Road::DrawRoad()
{
	if (swapping)
		InterpolateBiomes();

	Line* playerLine = actual->lines[(int)((position + playerZ) / segmentL) % actual->lines.size()];
	Line* baseLine = actual->lines[(int)(position / segmentL) % actual->lines.size()];
	float percent = (float)((position % (int)segmentL) / segmentL);
	float difX = -(baseLine->curve * percent);
	float sumX = 0;
	Line* l;

	playerLine->projection(playerLine->p1, (int)((playerX * ROAD_WIDTH) - sumX), (int)((float)cameraHeight + playerY), position, cameraDistance);
	float maxY = playerLine->p1.yScreen;

	for (int n = 0; n < drawDistance; n++) {
		l = actual->lines[(baseLine->index + n) % actual->lines.size()];
		l->clip = maxY;
		SDL_Color c1, c2, c3, c4;
		l->light ? c1 = sand : c1 = sand2;
		l->light ? c2 = road : c2 = road2;
		l->light ? c3 = rumble : c3 = rumble2;
		l->light ? c4 = lane : c4 = lane2;

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

		App->renderer->DrawPoly4(0, y1, SCREEN_WIDTH, y1, SCREEN_WIDTH, y2, 0, y2, c1);
		App->renderer->DrawPoly4(x1 - w1, y1, x1 + w1, y1, x2 + w2, y2, x2 - w2, y2, c2);
		App->renderer->DrawPoly4(x11 - w11, y11, x11 + w11, y11, x21 + w21, y21, x21 - w21, y21, c2);

		App->renderer->DrawPoly4(x1 - w1 - (int)(w1 / 7), y1, x1 + w1 + (int)(w1 / 7), y1, x2 + w2 + (int)(w2 / 7), y2, x2 - w2 - (int)(w2 / 7), y2, c3);
		App->renderer->DrawPoly4(x11 - w11 - (int)(w11 / 7), y11, x11 + w11 + (int)(w11 / 7), y11, x21 + w21 + (int)(w21 / 7), y21, x21 - w21 - (int)(w21 / 7), y21, c3);

		//Draw lines in road lanes (order matters for joining them together)
		App->renderer->DrawPoly4(x1 - w1, y1, x1 + w1, y1, x2 + w2, y2, x2 - w2, y2, c4);
		App->renderer->DrawPoly4(x11 - w11, y11, x11 + w11, y11, x21 + w21, y21, x21 - w21, y21, c4);

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18), y1, x1 + w1 - (w1 / 18), y1, x2 + w2 - (w2 / 18), y2, x2 - w2 + (w2 / 18), y2, c2);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18), y11, x11 + w11 - (w11 / 18), y11, x21 + w21 - (w21 / 18), y21, x21 - w21 + (w21 / 18), y21, c2);

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18) + (w1 * 16 / 27), y1, x1 + w1 - (w1 / 18) - (w1 * 16 / 27), y1, x2 + w2 - (w2 / 18) - (w2 * 16 / 27), y2, x2 - w2 + (w2 / 18) + (w2 * 16 / 27), y2, c4);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18) + (w11 * 16 / 27), y11, x11 + w11 - (w11 / 18) - (w11 * 16 / 27), y11, x21 + w21 - (w21 / 18) - (w21 * 16 / 27), y21, x21 - w21 + (w21 / 18) + (w21 * 16 / 27), y21, c4);

		App->renderer->DrawPoly4(x1 - w1 + (w1 / 18) * 2 + (w1 * 16 / 27), y1, x1 + w1 - (w1 / 18) * 2 - (w1 * 16 / 27), y1, x2 + w2 - (w2 / 18) * 2 - (w2 * 16 / 27), y2, x2 - w2 + (w2 / 18) * 2 + (w2 * 16 / 27), y2, c2);
		App->renderer->DrawPoly4(x11 - w11 + (w11 / 18) * 2 + (w11 * 16 / 27), y11, x11 + w11 - (w11 / 18) * 2 - (w11 * 16 / 27), y11, x21 + w21 - (w21 / 18) * 2 - (w21 * 16 / 27), y21, x21 - w21 + (w21 / 18) * 2 + (w21 * 16 / 27), y21, c2);

		maxY = l->p2.yScreen;
	}

	//Render sky background
	App->renderer->DrawQuad({ 0, 0, SCREEN_WIDTH, (int)maxY + SCREEN_Y_OFFSET }, 0, bg.r, bg.g, bg.b);

	//Render second background
	if (!swapping)
	{
		if (App->player->playerState != PlayerGAMEOVER)
		{
			if (!playerLine->mirror)
				offsetXBackground1 += playerLine->curve * (position - iniPosition) / SEGMENT_LENGTH * 2.f;
			if (offsetXBackground1 + SCREEN_WIDTH > backgroundLvl1.w)
				offsetXBackground1 = 0.f;
			if (offsetXBackground1 < 0.f)
				offsetXBackground1 = (float)(backgroundLvl1.w - SCREEN_WIDTH);
		}

		SDL_Rect dest = { backgroundLvl1.x + (int)offsetXBackground1, MAX(backgroundLvl1.y, backgroundLvl1.y + (backgroundLvl1.h - (int)(maxY + SCREEN_Y_OFFSET))), SCREEN_WIDTH, MIN(backgroundLvl1.h, (int)(maxY + SCREEN_Y_OFFSET)) };
		App->renderer->Blit(background1, 0, (int)(maxY + SCREEN_Y_OFFSET), &dest, 1.f, { 1.f, 1.f }, { 0.f, 1.f });
	}
	else
	{
		SDL_Rect dest = { backgroundLvl1.x + (int)offsetXBackground1, MAX(backgroundLvl1.y, backgroundLvl1.y + (backgroundLvl1.h - (int)(maxY + SCREEN_Y_OFFSET))), SCREEN_WIDTH, MIN(backgroundLvl1.h, (int)(maxY + SCREEN_Y_OFFSET)) };
		App->renderer->Blit(background1, 0 - (int)backgroundSwapOffset, (int)(maxY + SCREEN_Y_OFFSET), &dest, 1.f, { 1.f, 1.f }, { 0.f, 1.f });
		App->renderer->Blit(background2, SCREEN_WIDTH - (int)backgroundSwapOffset, (int)(maxY + SCREEN_Y_OFFSET), &dest, 1.f, { 1.f, 1.f }, { 0.f, 1.f });
	}
	//Draw sprites and cars
	for (int n = (int)(drawDistance - 1); n > 0; --n)
	{
		l = actual->lines[(baseLine->index + n) % actual->lines.size()];

		if (l->index < playerLine->index)
			continue;

		for (unsigned int i = 0; i < l->lineProps.size(); ++i)
		{
			Prop* p = l->lineProps[i];
			l->RenderProps(sprites, i);
		}

		Line* l2;
		for (unsigned int n = 0; n < active.size(); ++n)
		{
			l2 = actual->lines[(int)(active[n]->zPos / segmentL) % actual->lines.size()];
			if (l2->index == l->index && l2->index >= playerLine->index && l2->index < playerLine->index + drawDistance)
			{
				if (!ending)
					l2->RenderCars(cars, active[n]);
				else if (ending && active[n]->active)
					l2->RenderCars(cars, active[n]);
			}
		}
	}
}

void Road::ActivateAnims()
{
	//Activate animations of flagmen and light
	flagman->animLeft.speed = 0.12f;
	flagman->animRight.speed = 0.12f;
	trafficLight->animLeft.speed = 0.095f;
	trafficLight->animRight.speed = 0.095f;
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

void Road::AddSegment(float curve, float y, bool mirror, float dist, Biome* biome)
{
	int n = (int)biome->lines.size();
	Line* l = new Line();

	l->index = n;
	l->p1.zWorld = (float)(n * segmentL);
	l->p11.zWorld = l->p1.zWorld;
	l->p1.yWorld = (biome->lines.size() == 0 ? 0 : biome->lines[biome->lines.size() - 1]->p2.yWorld);
	l->p11.yWorld = l->p1.yWorld;
	l->p2.zWorld = (float)((n + 1) * segmentL);
	l->p21.zWorld = l->p2.zWorld;
	l->p2.yWorld = y;
	l->p21.yWorld = l->p2.yWorld;
	l->light = (int)((n / rumbleL)) % 2;
	l->curve = curve;
	l->mirror = mirror;
	l->distance = dist;
	biome->lines.push_back(l);
}

void Road::AddRoad(int enter, int hold, int leave, float curve, float y, bool mirror, int distance, Biome* biome)
{
	float firstY, dist, distPerc;
	float total = (float)(enter + hold + leave);
	if (mirror)
	{
		firstY = (biome->lines.size() == 0 ? 0 : biome->lines[biome->lines.size() - 1]->p2.yWorld);
		dist = biome->lines[biome->lines.size() - 1]->distance;
		distPerc = (float)((distM - dist)) / total;
	}
	else
	{
		if (biome->lines.size() == 0)
		{
			firstY = 0;
			dist = (float)distance;
			distPerc = 0;
		}
		else
		{
			firstY = biome->lines[biome->lines.size() - 1]->p2.yWorld;
			dist = biome->lines[biome->lines.size() - 1]->distance;
			distPerc = (float)((distance - dist)) / total;
		}
	}

	float endY = firstY + y * segmentL;
	int n;
	for (n = 0; n < enter; ++n)
	{
		dist += (int)distPerc;
		AddSegment(EaseIn(0, curve, (float)n / enter), EaseInOut(firstY, endY, (float)n / total), mirror, dist, biome);
	}
	for (n = 0; n < hold; ++n)
	{
		dist += (int)distPerc;
		AddSegment(curve, EaseInOut(firstY, endY, (float)(enter + n) / total), mirror, dist, biome);

		if (n == (int)(hold / 2))
			if (mirror && biome->swapLine == 0)
				biome->swapLine = (int)biome->lines.size();
	}
	for (n = 0; n < leave; ++n)
	{
		dist += (int)distPerc;
		AddSegment(EaseInOut(curve, 0, (float)n / leave), EaseInOut(firstY, endY, (float)(enter + hold + n) / total), mirror, dist, biome);
	}
	if (mirror && biome->lastLine == 0)
		biome->lastLine = (int)biome->lines.size();
}

void Road::AddStraight(int num, bool mirror, int distance, Biome* biome)
{
	AddRoad(num, num, num, 0, 0, mirror, distance, biome);
}

void Road::AddCurve(int num, float curve, bool mirror, int distance, int length, Biome* biome)
{
	AddRoad(num, num*length, num, curve, 0, mirror, distance, biome);
}

void Road::AddHill(int num, float y, int distance, int length, Biome* biome)
{
	AddRoad(num, num*length, num, 0, y, false, distance, biome);
}

void Road::AddProp(unsigned int line, Prop* p, float offsetX, float offsetY, bool side, Biome* biome)
{
	if (line < biome->lines.size())
	{
		biome->lines[line]->lineProps.push_back(p);
		biome->lines[line]->offsetsX.push_back(offsetX);
		biome->lines[line]->offsetsY.push_back(offsetY);
		biome->lines[line]->sides.push_back(side);
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

void Road::UpdateCars(float time)
{
	Line* l;
	for (unsigned int i = 0; i < active.size(); ++i)
	{
		Car* c = active[i];
		c->zPos += c->speed;
		l = actual->lines[(int)((c->zPos) / segmentL) % actual->lines.size()];
		Line* playerLine = actual->lines[(int)((position + playerZ) / segmentL) % actual->lines.size()];
		switch (c->active)
		{
		case false:
			if (l->index < playerLine->index + drawDistance && l->index > playerLine->index)
			{
				c->active = true;
				c->speed = 120.f;
			}
			break;
		case true:
			if (l->index > playerLine->index + drawDistance || l->index < playerLine->index)
			{
				if (l->index < playerLine->index)
					App->player->score += 20000;
				c->side = rand() % 2;
				c->active = false;
				c->speed = 0.f;
				c->zPos += (rand() % (680) + 220)*SEGMENT_LENGTH;
			}
			break;
		}
		float posCar = (c->side ? c->offset * ROAD_WIDTH + roadDistance : c->offset * ROAD_WIDTH);
		if (posCar > playerX * ROAD_WIDTH)
			c->current_anim = &c->left;
		else
			c->current_anim = &c->right;
	}
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

				else if (speed >= 80 && speed <= 100) {
					App->player->current_animation = &(App->player->crash2);
					//Collision animation time to stop at 0.8 (1 turn)
					App->player->lowAccel = (speed / 0.8f);
					App->player->playerState = MEDIUMCOLLISION;
				}
				else if (speed > 100 && speed <= 150) {
					App->player->current_animation = &(App->player->crash21);
					//Collision animation time to stop at 1.6 (2 turns)
					App->player->lowAccel = (speed / 1.6f);
					App->player->playerState = MEDIUMCOLLISION;
				}
			}
		}
	}

	for (unsigned int n = 0; n < active.size(); ++n)
	{
		Car* c = active[n];
		Line* lc = actual->lines[(int)(c->zPos / segmentL) % actual->lines.size()];
		if (App->player->playerState == ONROAD && lc->index == playerLine->index)
		{
			PointLine point = playerLine->p1;
			PointLine point2 = playerLine->p2;
			if (c->side)
			{
				point = playerLine->p11;
				point2 = playerLine->p21;
			}

			float perc = (float)(((int)(c->zPos) % (int)SEGMENT_LENGTH) / (float)SEGMENT_LENGTH);
			float scaleOffset = point.scale + (point2.scale - point.scale)*perc;
			float xOffset = point.xScreen + (point2.xScreen - point.xScreen)*perc;
			float yOffset = point.yScreen + (point2.yScreen - point.yScreen)*perc;

			float x2 = xOffset + (c->offset * scaleOffset * ROAD_WIDTH * SCREEN_WIDTH / 2);
			float scale = 1.6f * (0.3f * (1.f / 170.f)) * scaleOffset * SCREEN_WIDTH * ROAD_WIDTH * 1.2f;

			if (Collides((float)(SCREEN_WIDTH / 2) + 5.f, playerW, x2, (float)c->left.GetCurrentFrame().w, scale))
			{
				collisionDir = playerX;
				float speed = App->player->speed;
				if (speed < 80) {
					App->player->current_animation = &(App->player->crash1);
					App->player->playerState = SMALLCOLLISION;
				}

				else if (speed >= 80 && speed <= 100) {
					App->player->current_animation = &(App->player->crash2);
					//Collision animation time to stop at 0.8 (1 turn)
					App->player->lowAccel = (speed / 0.8f);
					App->player->playerState = MEDIUMCOLLISION;
				}
				else if (speed > 100 && speed <= 150) {
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

	return (max1 >= min2 && max2 >= min1);
}

void Road::InterpolateBiomes()
{
	if (backgroundSwapOffset < SCREEN_WIDTH)
	{
		backgroundSwapOffset += 5.f;
		if (backgroundSwapOffset > SCREEN_WIDTH)
			backgroundSwapOffset = SCREEN_WIDTH;
	}

	bg = InterpolateColors(bg, bg2);
	sand = InterpolateColors(sand, sandAux);
	sand2 = InterpolateColors(sand2, sand2Aux);
	road = InterpolateColors(road, roadAux);
	road2 = InterpolateColors(road2, road2Aux);
	rumble = InterpolateColors(rumble, rumbleAux);
	rumble2 = InterpolateColors(rumble2, rumble2Aux);
	lane = InterpolateColors(lane, laneAux);
	lane2 = InterpolateColors(lane2, lane2Aux);

	if (backgroundSwapOffset >= SCREEN_WIDTH && SameColor(bg, bg2) && SameColor(sand, sandAux) && SameColor(sand2, sand2Aux) && SameColor(road, roadAux) && SameColor(road2, road2Aux) &&
		SameColor(rumble, rumbleAux) && SameColor(rumble2, rumble2Aux) && SameColor(lane, laneAux) && SameColor(lane2, lane2Aux))
	{
		background1 = background2;
		backgroundSwapOffset = 0.f;
		swapping = false;
		actual->biomeSwap = true;
	}
}