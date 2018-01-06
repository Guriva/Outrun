#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHighscore.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFontManager.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMain.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include <fstream>
#include <string>

ModuleSceneHighscore::ModuleSceneHighscore(bool active) : Module(active)
{
	route1 = { 1, 1, 16, 11 };
	letters = "abcdefghijklmnopqrstuvwxyz.<;";
}

ModuleSceneHighscore::~ModuleSceneHighscore()
{

}

bool ModuleSceneHighscore::Start()
{
	tick_timer = clock();
	recordTimer = 30.f;
	passTimer = 5.f;
	pos = 0;
	score = App->score;
	totalTime = App->totalTime;
	index = 0;
	recordName = "";

	scores.clear();
	names.clear();
	routes.clear();
	records.clear();

	scores.reserve(7);
	names.reserve(7);
	routes.reserve(7);
	records.reserve(7);

	ifstream file;
	file.open("highscoreData.txt");
	int n, s, r;
	string name;
	float rec;
	if (file.is_open())
	{
		file >> n;
		if (n > 7) n = 7;
		while (n > 0)
		{
			file >> s;
			scores.push_back(s);
			file >> name;
			names.push_back(name);
			file >> r;
			routes.push_back(r);
			file >> rec;
			records.push_back(rec);
			--n;
		}
	}
	file.close();

	bool found = false;
	//Set position on ranking
	for (unsigned int i = 0; i < scores.size() && !found; ++i)
	{
		if (scores[i] < score)
		{
			pos = i + 1;
			found = true;
		}
	}

	App->audio->PlayMusic("Audio/LastWave.ogg", 0.f);

	layout = App->textures->Load("Textures/Highscore/highscoreLayout.png");
	spritesRoute = App->textures->Load("Textures/Highscore/routeSprites.png");
	App->fonts->loadFont("yellowhigh", "Textures/Fonts/highscoreFont.png", "abcdefghijklmnopqrstuvwxyz.<;", 8, 16);
	App->fonts->loadFont("redhigh", "Textures/Fonts/redhighscoreFont.png", "abcdefghijklmnopqrstuvwxyz.<;0123456789", 8, 16);
	App->fonts->loadFont("green", "Textures/Fonts/greenFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);
	App->fonts->loadFont("blue", "Textures/Fonts/blueFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ '^", 8, 8);
	App->fonts->loadFont("pink", "Textures/Fonts/pinkFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);

	return true;
}

update_status ModuleSceneHighscore::Update()
{
	time = (float)((clock() - tick_timer) / (double)CLOCKS_PER_SEC);
	tick_timer = clock();

	App->renderer->Blit(layout, (int)(SCREEN_WIDTH / 2.f), (int)(SCREEN_HEIGHT / 2.f), nullptr, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });

	//New score
	if (score > scores[scores.size() - 1])
	{
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN && index > 0)
			--index;
		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN && index < 28)
			++index;
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			//End
			if (index == 28)
				recordTimer = 0.f;
			//Erase one letter
			else if (index == 27)
			{
				if (recordName.length() > 0)
					recordName.pop_back();
			}
			//Add letter to name
			else if (recordName.length() < 3)
				recordName += letters[index];
		}
		
		App->fonts->print(to_string((int)recordTimer).c_str(), 820, 135, "redhigh", { 3.2f, 3.43f }, { 1.f, 1.f });
		App->fonts->print((to_string(pos + 1) + ".").c_str(), 180, 250 + 50 * (pos-1), "pink", { 3.2f, 3.43f }, { 1.f, 1.f });
		App->fonts->print(to_string(score).c_str(), 400, 250 + 50 * (pos-1), "blue", { 3.2f, 3.43f }, { 1.f, 1.f });
		App->fonts->print(recordName.c_str(), 443, 250 + 50 * (pos-1), "green", { 3.2f, 3.43f }, { 0.f, 1.f });
		App->renderer->Blit(spritesRoute, 640, 250 + 50 * (pos-1), &route1, 1.f, { 3.2f, 3.43f }, { 1.f, 1.f });
		int min = (int)(totalTime / 60.f);
		int sec = (int)((int)(totalTime - (float)(min * 60)));
		int mili = (int)((int)((totalTime - (int)(totalTime)) * 100.f));
		string minS = to_string(min);
		string secS = to_string(sec);
		if (sec < 10)
			secS = "0" + secS;
		string miliS = to_string(mili);
		if (mili < 10)
			miliS = "0" + miliS;
		App->fonts->print((minS + "'" + secS + "^" + miliS).c_str(), 900, 250 + 50 * (pos-1), "blue", { 3.2f, 3.43f }, { 1.f, 1.f });
		App->fonts->print("abcdefghijklmnopqrstuvwxyz.<;", 157, 670, "yellowhigh", { 3.2f, 3.43f }, { 0.f, 1.f });
		string saux(1, letters[index]);
		App->fonts->print(saux.c_str(), 183 + (int)(25.6f * (float)index), 670, "redhigh", { 3.2f, 3.43f }, { 1.f, 1.f });

		recordTimer -= time;
		if (recordTimer < 0.f)
		{
			if (recordName.length() > 0)
			{
				ofstream file;
				file.open("highscoreData.txt");
				unsigned int n = scores.size();
				file << n << endl;
				for (unsigned int i = 0; i < scores.size(); ++i)
				{
					if (i + 1 == pos)
					{
						file << score << " " << recordName << " " << 1 << " " << totalTime << endl;
					}
					else
						file << scores[i] << " " << names[i] << " " << routes[i] << " " << records[i] << endl;
				}
				file.close();
			}
			App->fade->FadeToBlack(App->scene_main, this, 0.f);
		}
	}
	else
	{
		passTimer -= time;
		if (passTimer < 0.f)
		{
			App->audio->StopMusic(0.f);
			App->fade->FadeToBlack(App->scene_main, this, 0.f);
		}
	}

	//Print data
	for (unsigned int i = 0; i < scores.size(); ++i)
	{
		if (i + 1 != pos)
		{
			App->fonts->print((to_string(i+1) + ".").c_str(), 180, 250 + 50 * i, "pink", { 3.2f, 3.43f }, { 1.f, 1.f });
			App->fonts->print(to_string(scores[i]).c_str(), 400, 250 + 50 * i, "blue", { 3.2f, 3.43f }, { 1.f, 1.f });
			App->fonts->print(names[i].c_str(), 520, 250 + 50 * i, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
			if (routes[i] != -1)
				App->renderer->Blit(spritesRoute, 640, 250 + 50 * i, &route1, 1.f, { 3.2f, 3.43f }, { 1.f, 1.f });
			if (records[i] != -1)
			{
				int min = (int)(records[i] / 60.f);
				int sec = (int)((int)(records[i] - (float)(min * 60)));
				int mili = (int)((int)((records[i] - (int)(records[i])) * 100.f));
				string minS = to_string(min);
				string secS = to_string(sec);
				if (sec < 10)
					secS = "0" + secS;
				string miliS = to_string(mili);
				if (mili < 10)
					miliS = "0" + miliS;
				App->fonts->print((minS + "'" + secS + "^" + miliS).c_str(), 900, 250 + 50 * i, "blue", { 3.2f, 3.43f }, { 1.f, 1.f });
			}
		}
	}
	App->fonts->print("credit", 58, 733, "pink", { 3.2f, 3.43f });
	App->fonts->print(to_string(App->credit).c_str(), 256, 733, "pink", { 3.2f, 3.43f });
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneHighscore::CleanUp()
{
	App->textures->Unload(layout);
	App->textures->Unload(spritesRoute);
	App->fonts->closeFont("yellowhigh");
	App->fonts->closeFont("redhigh");
	App->fonts->closeFont("green");
	App->fonts->closeFont("blue");
	App->fonts->closeFont("pink");
	return true;
}