#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "Line.h"

using namespace std;

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{
	cameraDistance = 1 / tan((float)((FOV / 2.f) * M_PI / 180.0f));
	int a = 0;
}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading level scene");

	for (int i = 0; i < ROAD_LENGTH; ++i) {
		Line* l = new Line();
		l->zWorld = (float)i;
		lines.push_back(l);
	}

	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading level scene");

	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	/*for (int i = 0; i < SCREEN_HEIGHT / 2; ++i)
		App->renderer->DrawQuad({ i,SCREEN_HEIGHT - i + 1,SCREEN_WIDTH - i*2,1 }, 255, 0, 0, 255);*/

	//Render road
	for (int i = 0; i < DRAW_DISTANCE; ++i) {
		Line *l = lines[i%lines.size()];
		l->projection(0,CAMERA_HEIGHT,0,cameraDistance);
		//Set Colors
		(i / RUMBLE_LENGTH) % 2 ? sand = { 230, 214, 197, 255 } : sand = { 239, 222, 206, 255 };
		(i / RUMBLE_LENGTH) % 2 ? road = { 156, 156, 156, 255 } : road = { 148, 148, 148, 255 };
		(i / RUMBLE_LENGTH) % 2 ? rumble = { 247, 247, 247, 255 } : rumble = { 0, 0, 0, 0 };
		(i / RUMBLE_LENGTH) % 2 ? lane = { 247, 247, 247, 255 } : lane = { 0, 0, 0, 0 };
		App->renderer->DrawQuad({ 0, (int)(l->yScreen), SCREEN_WIDTH, 1 }, sand.r, sand.g, sand.b, sand.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen), (int)(l->yScreen), (int)(l->wScreen * 2), 1 }, road.r, road.g, road.b, road.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen), (int)(l->yScreen), (int)(l->wScreen * 2), 1 }, rumble.r, rumble.g, rumble.b, rumble.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen/1.15f), (int)(l->yScreen), (int)(l->wScreen * 2.f / 1.15f), 1}, road.r, road.g, road.b, road.a);
	}
	return UPDATE_CONTINUE;
}