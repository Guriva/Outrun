#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Road.h"

using namespace std;

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{
	tick_timer = clock();
	road = new Road();
}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading level scene");
	App->player->Enable();
	//App->particles->Enable();

	road->InitRoad();

	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading level scene"); 
	/*** TODO !!***/

	road->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	time = (float)((clock() - tick_timer) / (double)CLOCKS_PER_SEC);
	tick_timer = clock();

	road->RenderRoad(time);

	return UPDATE_CONTINUE;
}