#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleSceneMain.h"
#include "ModuleSceneLevel.h"
#include "ModuleFontManager.h"

using namespace std;

Application::Application()
{
	tick_timer = clock();
	// Order matters: they will init/start/pre/update/post in this order
	modules.push_back(input = new ModuleInput());
	modules.push_back(window = new ModuleWindow());

	modules.push_back(renderer = new ModuleRender());
	modules.push_back(textures = new ModuleTextures());
	modules.push_back(fonts = new ModuleFontManager());
	modules.push_back(audio = new ModuleAudio());

	// Game Modules
	modules.push_back(scene_main = new ModuleSceneMain(false));
	modules.push_back(scene_level = new ModuleSceneLevel(false));
	modules.push_back(player = new ModulePlayer(false));

	// Modules to draw on top of game logic
	modules.push_back(collision = new ModuleCollision());		//If initial load takes too long, modify to load it on specific scene
	modules.push_back(particles = new ModuleParticles());
	modules.push_back(fade = new ModuleFadeToBlack());
}

Application::~Application()
{
	for (list<Module*>::iterator it = modules.begin(); it != modules.end(); ++it)
		RELEASE(*it);
}

bool Application::Init()
{
	bool ret = true;

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
		ret = (*it)->Init(); // we init everything, even if not enabled

	for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret; ++it)
	{
		if ((*it)->IsEnabled() == true)
			ret = (*it)->Start();
	}

	// Start the first scene --
	fade->FadeToBlack(scene_level, nullptr, 0.f);

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	clock_t now = clock();
	float time = float(now - tick_timer) / CLOCKS_PER_SEC;
	if (time > 1 / TICK_FPS)
	{
		float t = time;
		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled() == true)
				ret = (*it)->PreUpdate(time);

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled() == true)
				ret = (*it)->Update(time);

		for (list<Module*>::iterator it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
			if ((*it)->IsEnabled() == true)
				ret = (*it)->PostUpdate(time);

		tick_timer = now;
		LOG("time is %f", time);
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (list<Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend() && ret; ++it)
		if ((*it)->IsEnabled() == true)
			ret = (*it)->CleanUp();

	return ret;
}

