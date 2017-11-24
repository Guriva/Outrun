#include "Globals.h"
#include "Application.h"
#include "ModuleSceneMain.h"

using namespace std;

ModuleSceneMain::ModuleSceneMain(bool active) : Module(active)
{}

ModuleSceneMain::~ModuleSceneMain()
{}

// Load assets
bool ModuleSceneMain::Start()
{
	LOG("Loading main scene");

	return true;
}

// UnLoad assets
bool ModuleSceneMain::CleanUp()
{
	LOG("Unloading main scene");

	return true;
}

// Update: draw background
update_status ModuleSceneMain::Update()
{
	return UPDATE_CONTINUE;
}