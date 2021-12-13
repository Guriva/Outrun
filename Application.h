#ifndef __APPLICATION_CPP__
#define __APPLICATION_CPP__

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleFontManager;
class ModuleInput;
class ModuleAudio;
class ModuleFadeToBlack;

// Game modules ---
class ModulePlayer;
class ModuleSceneMain;
class ModuleSceneLevel;
class ModuleSceneHighscore;
class ModuleUI;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleFontManager* fonts;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleFadeToBlack* fade;

	// Game modules ---
	ModulePlayer* player;
	ModuleSceneMain* scene_main;
	ModuleSceneLevel* scene_level;
	ModuleSceneHighscore* highscore;
	ModuleUI* ui;

	int score;
	unsigned int credit;
	float totalTime;
	const char* musicLevel = nullptr;

	//FPS Cap ---
	int lastTime;

private:
	std::list<Module*> modules;
};

extern Application* App;

#endif // __APPLICATION_CPP__