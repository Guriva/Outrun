#ifndef __ModuleSceneHighscore_H__
#define __ModuleSceneHighscore_H__

#include "Module.h"
#include "Animation.h"
#include <ctime>
#include <vector>

using namespace std;

struct SDL_Texture;

class ModuleSceneHighscore : public Module
{
public:
	ModuleSceneHighscore(bool active = true);
	~ModuleSceneHighscore();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* layout;
	SDL_Texture* spritesRoute;
	float recordTimer, passTimer, time;
	int pos, score, index;
	float totalTime;
	SDL_Rect route1;
	vector<int> scores;
	vector<string> names;
	vector<int> routes;
	vector<float> records;
	string letters, recordName;
	clock_t tick_timer;
};

#endif // __MODULESCENEHIGHSCORE_H__