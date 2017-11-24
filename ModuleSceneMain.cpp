#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMain.h"
#include "ModuleFontManager.h"
#include "SDL_timer.h"
#include <string>

using namespace std;

ModuleSceneMain::ModuleSceneMain(bool active) : Module(active)
{
	iniTime = (float)(SDL_GetTicks());
	countdown = 15.f;
	credit = 0;
	music = 1;
	fxWavePlayed = false;

	logo.frames.push_back({ 1,1,176,88 });
	logo.frames.push_back({ 1,90,176,88 });
	logo.frames.push_back({ 1,179,176,88 });
	logo.frames.push_back({ 1,90,176,88 });
	logo.frames.push_back({ 1,90,176,88 });
	logo.frames.push_back({ 178,1,176,88 });
	logo.frames.push_back({ 178,90,176,88 });
	logo.frames.push_back({ 178,179,176,88 });
	logo.frames.push_back({ 178,179,176,88 });
	logo.frames.push_back({ 178,90,176,88 });
	logo.frames.push_back({ 178,1,176,88 });
	logo.frames.push_back({ 1,179,176,88 });
	logo.frames.push_back({ 1,179,176,88 });
	logo.frames.push_back({ 1,90,176,88 });
	logo.speed = 0.02f;

	car.frames.push_back({ 355,1,64,39 });
	car.frames.push_back({ 355,41,64,39 });
	car.speed = 0.3f;

	palm.frames.push_back({ 355,81,37,29 });
	palm.frames.push_back({ 355,111,37,29 });
	palm.frames.push_back({ 355,141,37,29 });
	palm.frames.push_back({ 355,111,37,29 });
	palm.speed = 0.2f;

	insertCoins.frames.push_back({ 1,1,104,8 });
	insertCoins.frames.push_back({ 0,0,0,0 });
	insertCoins.speed = 0.03f;

	pressStart.frames.push_back({ 1,10,157,8 });
	pressStart.frames.push_back({ 0,0,0,0 });
	pressStart.speed = 0.03f;

	radioLeds.frames.push_back({ 128,0,48,9 });
	radioLeds.frames.push_back({ 128,10,48,9 });
	radioLeds.frames.push_back({ 128,20,48,9 });
	radioLeds.frames.push_back({ 128,30,48,9 });
	radioLeds.frames.push_back({ 128,40,48,9 });
	radioLeds.frames.push_back({ 128,50,48,9 });
	radioLeds.frames.push_back({ 128,60,48,9 });
	radioLeds.frames.push_back({ 128,70,48,9 });
	radioLeds.speed = 0.25f;

	radioNum.push_back({ 1,1,126,30 });
	radioNum.push_back({ 1,32,126,30 });
	radioNum.push_back({ 1,63,126,30 });

	radioMusic.push_back({ 1,94,175,16 });
	radioMusic.push_back({ 1,111,175,16 });
	radioMusic.push_back({ 1,128,175,16 });

	radioHand.push_back({ 177,1,133,59 });
	radioHand.push_back({ 177,61,133,59 });
	radioHand.push_back({ 177,121,133,59 });
}

ModuleSceneMain::~ModuleSceneMain()
{}

// Load assets
bool ModuleSceneMain::Start()
{
	LOG("Loading logo scene");

	logoTexture = App->textures->Load("Textures/Main/LogoMain.png");
	radioTexture = App->textures->Load("Textures/Main/radio.png");
	background = App->textures->Load("Textures/Main/backgroundMain.png");
	background2 = App->textures->Load("Textures/Main/background2Main.png");
	letters = App->textures->Load("Textures/Main/flashLetters.png");
	App->fonts->loadFont("green", "Textures/Fonts/greenFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);
	App->fonts->loadFont("blue", "Textures/Fonts/blueFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);
	App->fonts->loadFont("pink", "Textures/Fonts/pinkFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);

	audioCoin = App->audio->LoadFx("Audio/creditInsert.wav");
	audioWave = App->audio->LoadFx("Audio/waveSound.wav");

	return true;
}

// UnLoad assets
bool ModuleSceneMain::CleanUp()
{
	LOG("Unloading logo scene");

	App->textures->Unload(logoTexture);
	App->textures->Unload(background);
	App->textures->Unload(radioTexture);
	App->textures->Unload(background2);
	App->textures->Unload(letters);

	return true;
}

// Update: draw background
update_status ModuleSceneMain::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && credit < 9)
	{
		++credit;
		App->audio->PlayFx(audioCoin);
		//Make sound of credit
	}
	if (credit == 0)
	{
		App->renderer->Blit(background, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(logoTexture, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), &(logo.GetCurrentFrame()), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(logoTexture, (int)(SCREEN_WIDTH / 2) - 2, (int)(SCREEN_HEIGHT / 2) + 24, &(car.GetCurrentFrame()), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(logoTexture, (int)(SCREEN_WIDTH / 2) - 58, (int)(SCREEN_HEIGHT / 2) - 17, &(palm.GetCurrentFrame()), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(letters, (int)(SCREEN_WIDTH / 2) - 4, (int)(SCREEN_HEIGHT / 2) + 60, &(insertCoins.GetCurrentFrame()), 1.f, 1.f, { 0.5f, 0.5f });
		App->fonts->print("1986 @sega", 232, 208, "blue");
	}
	else
	{
		if (fxWavePlayed == false)
			fxWavePlayed = App->audio->PlayFx(audioWave, 3);
		switch (music)
		{
		case 0:
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
				music = 1;
			break;
		case 1:
			if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
				music = 0;
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
				music = 2;
			break;
		case 2:
			if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
				music = 1;
			break;
		}
		App->renderer->Blit(background2, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) - 8, (int)(SCREEN_HEIGHT / 2) - 16, &(radioMusic[music]), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) + 31, (int)(SCREEN_HEIGHT / 2) + 69, &(radioNum[music]), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) + 1, (int)(SCREEN_HEIGHT / 2) + 78, &(radioLeds.GetCurrentFrame()), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) + 26, (int)(SCREEN_HEIGHT / 2) + 83, &(radioHand[music]), 1.f, 1.f, { 0.5f, 0.5f });
		App->renderer->Blit(letters, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2) + 44, &(pressStart.GetCurrentFrame()), 1.f, 1.f, { 0.5f, 0.5f });
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			//***Change scene***//
			//Pass music value
		}
	}
	App->fonts->print("credit", 18, 208, "pink");
	App->fonts->print(to_string(credit).c_str(), 80, 208, "pink");

	return UPDATE_CONTINUE;
}