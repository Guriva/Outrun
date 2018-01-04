#include "Application.h"
#include "ModuleSceneLevel.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Road.h"

using namespace std;

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{
	road = new Road();
	actualState = COUNTDOWN;
	countdownTimer = 5.0f;
}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading level scene");
	tick_timer = clock();
	App->player->Enable();
	//App->particles->Enable();
	road->Start();
	road->InitRoad();

	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading level scene");
	/*** TODO !!***/

	road->CleanUp();
	RELEASE(road);

	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	time = (float)((clock() - tick_timer) / (double)CLOCKS_PER_SEC);
	tick_timer = clock();

	switch (actualState)
	{
	case COUNTDOWN:
		if (countdownTimer < 4.0f)
			App->player->preparingAnim.speed = 0.1f;
		if (countdownTimer < 2.0f)
			road->ActivateAnims();

		countdownTimer -= time;

		if (countdownTimer < 0)
		{
			actualState = RUNNING;
			App->player->playerState = ONROAD;
		}
		road->DrawRoad();
		break;
	case RUNNING:
		road->UpdateRoad(time);
		road->DrawRoad();
		if (road->ending)
			actualState = FINISH;
		break;
	case FINISH:
		road->UpdateRoadEnding(time);
		road->DrawRoad();
		break;
	}

	return UPDATE_CONTINUE;
}