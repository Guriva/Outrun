#include "Globals.h"
#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleRender.h"
#include "Line.h"
#include "ModulePlayer.h"

using namespace std;

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{
	cameraDistance = 1 / tan((float)((FOV / 2.f) * M_PI / 180.0f));
	cameraZ = 0.f;
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
update_status ModuleSceneLevel::Update()
{
	//Render sky background
	App->renderer->DrawQuad({ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, 0, 148, 255, 255);
	//Render second background

	//Render third background

	//Calculate CameraZ depending on car
	cameraZ += App->player->speed;
	while (cameraZ > lines.size()) cameraZ -= lines.size();
	while (cameraZ < 0) cameraZ += lines.size();

	//Render road
	for (int i = cameraZ; i < cameraZ+DRAW_DISTANCE; ++i) {
		Line *l = lines[i%lines.size()];
		l->projection(App->player->xPos * ROAD_WIDTH,CAMERA_HEIGHT - (i >= lines.size() ? lines.size() : 0), cameraZ,cameraDistance);
		//Set Colors
		(i / RUMBLE_LENGTH) % 2 ? sand = { 230, 214, 197, 255 } : sand = { 239, 222, 206, 255 };
		(i / RUMBLE_LENGTH) % 2 ? road = { 156, 156, 156, 255 } : road = { 148, 148, 148, 255 };
		(i / RUMBLE_LENGTH) % 2 ? rumble = { 247, 247, 247, 255 } : rumble = { 0, 0, 0, 0 };
		(i / RUMBLE_LENGTH) % 2 ? lane = { 156, 156, 156, 255 } : lane = { 247, 247, 247, 255 };
		App->renderer->DrawQuad({ 0, (int)(l->yScreen), SCREEN_WIDTH, 1 }, sand.r, sand.g, sand.b, sand.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen * RUMBLE_WIDTH), (int)(l->yScreen), (int)(l->wScreen * 2 * RUMBLE_WIDTH), 1 }, road.r, road.g, road.b, road.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen * RUMBLE_WIDTH), (int)(l->yScreen), (int)(l->wScreen * 2 * RUMBLE_WIDTH), 1 }, rumble.r, rumble.g, rumble.b, rumble.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen), (int)(l->yScreen), (int)(l->wScreen * 2.f), 1 }, lane.r, lane.g, lane.b, lane.a);
		App->renderer->DrawQuad({ (int)(l->xScreen - l->wScreen * 0.96), (int)(l->yScreen), (int)(l->wScreen * 2.f * 0.96), 1 }, road.r, road.g, road.b, road.a);

		if (l->zCamera <= cameraDistance || l->yScreen >= SCREEN_HEIGHT)
			continue;

		float w = l->wScreen * 2 / ROAD_LANES;
		for (int i = 1; i < ROAD_LANES; ++i) {
			//App->renderer->DrawQuad();
		}
	}
	return UPDATE_CONTINUE;
}