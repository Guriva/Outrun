#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneMain.h"
#include "ModuleSceneLevel.h"
#include "ModuleFontManager.h"
#include "SDL_timer.h"
#include <string>

using namespace std;

ModuleSceneMain::ModuleSceneMain(bool active) : Module(active)
{
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

	car.frames.push_back({ 355,1,64,39 });
	car.frames.push_back({ 355,41,64,39 });

	palm.frames.push_back({ 355,81,37,29 });
	palm.frames.push_back({ 355,111,37,29 });
	palm.frames.push_back({ 355,141,37,29 });
	palm.frames.push_back({ 355,111,37,29 });

	insertCoins.frames.push_back({ 1,1,104,8 });
	insertCoins.frames.push_back({ 0,0,0,0 });

	pressStart.frames.push_back({ 1,10,157,8 });
	pressStart.frames.push_back({ 0,0,0,0 });

	radioLeds.frames.push_back({ 128,0,48,9 });
	radioLeds.frames.push_back({ 128,10,48,9 });
	radioLeds.frames.push_back({ 128,20,48,9 });
	radioLeds.frames.push_back({ 128,30,48,9 });
	radioLeds.frames.push_back({ 128,40,48,9 });
	radioLeds.frames.push_back({ 128,50,48,9 });
	radioLeds.frames.push_back({ 128,60,48,9 });
	radioLeds.frames.push_back({ 128,70,48,9 });

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

bool ModuleSceneMain::Init()
{
	App->fonts->loadFont("yellowhigh", "Textures/Fonts/highscoreFont.png", "abcdefghijklmnopqrstuvwxyz.<;", 8, 16);
	App->fonts->loadFont("redhigh", "Textures/Fonts/redhighscoreFont.png", "abcdefghijklmnopqrstuvwxyz.<;0123456789", 8, 16);
	App->fonts->loadFont("time", "Textures/Fonts/timeFont.png", "0123456789", 8, 14);
	App->fonts->loadFont("speed", "Textures/Fonts/speedFont.png", "0123456789", 8, 14);
	App->fonts->loadFont("green", "Textures/Fonts/greenFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);
	App->fonts->loadFont("blue", "Textures/Fonts/blueFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ '^", 8, 8);
	App->fonts->loadFont("pink", "Textures/Fonts/pinkFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);

	return true;
}

// Load assets
bool ModuleSceneMain::Start()
{
	countdown = 15.f;
	music = 1;
	fxWavePlayed = false;

	logo.speed = 0.02f;
	car.speed = 0.3f;
	palm.speed = 0.2f;
	insertCoins.speed = 0.03f;
	pressStart.speed = 0.03f;
	radioLeds.speed = 0.25f;

	logoTexture = App->textures->Load("Textures/Main/LogoMain.png");
	radioTexture = App->textures->Load("Textures/Main/radio.png");
	background = App->textures->Load("Textures/Main/backgroundMain.png");
	background2 = App->textures->Load("Textures/Main/background2Main.png");
	letters = App->textures->Load("Textures/Main/flashLetters.png");
	audioCoin = App->audio->LoadFx("Audio/creditInsert.wav");
	audioWave = App->audio->LoadFx("Audio/waveSound.wav");

	return true;
}

// UnLoad assets
bool ModuleSceneMain::CleanUp()
{
	App->textures->Unload(logoTexture);
	App->textures->Unload(radioTexture);
	App->textures->Unload(background);
	App->textures->Unload(background2);
	App->textures->Unload(letters);

	return true;
}

// Update: draw background
update_status ModuleSceneMain::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && App->credit < 9)
	{
		++App->credit;
		App->audio->PlayFx(audioCoin);
		//Make sound of credit
	}
	if (App->credit == 0)
	{
		App->renderer->Blit(background, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(logoTexture, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), &(logo.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(logoTexture, (int)(SCREEN_WIDTH / 2) - 19, (int)(SCREEN_HEIGHT / 2) + 81, &(car.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(logoTexture, (int)(SCREEN_WIDTH / 2) - 186, (int)(SCREEN_HEIGHT / 2) - 58, &(palm.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(letters, (int)(SCREEN_WIDTH / 2) - 4, (int)(SCREEN_HEIGHT / 2) + 206, &(insertCoins.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->fonts->print("1986 @sega", 742, 733, "blue", { 3.2f, 3.43f });
	}
	else
	{
		if (fxWavePlayed == false)
		{
			fxWavePlayed = true;
			fxWavePlayed = App->audio->PlayFx(audioWave, 3);
		}

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
		App->renderer->Blit(background2, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) - 26, (int)(SCREEN_HEIGHT / 2) - 55, &(radioMusic[music]), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) + 99, (int)(SCREEN_HEIGHT / 2) + 237, &(radioNum[music]), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) + 3, (int)(SCREEN_HEIGHT / 2) + 268, &(radioLeds.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(radioTexture, (int)(SCREEN_WIDTH / 2) + 83, (int)(SCREEN_HEIGHT / 2) + 285, &(radioHand[music]), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		App->renderer->Blit(letters, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2) + 151, &(pressStart.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {
			--App->credit;
			fxWavePlayed = false;
			switch (music)
			{
			case 0:
				App->musicLevel = "Audio/MagicalSoundShower.ogg";
				break;
			case 1:
				App->musicLevel = "Audio/PassingBreeze.ogg";
				break;
			case 2:
				App->musicLevel = "Audio/SplashWave.ogg";
				break;
			}
			if (App->fade->isFading() == false)
			{
				App->audio->StopFx();
				App->fade->FadeToBlack(App->scene_level, this, 0.f);
			}
		}
	}
	App->fonts->print("credit", 58, 733, "pink", { 3.2f, 3.43f });
	App->fonts->print(to_string(App->credit).c_str(), 256, 733, "pink", { 3.2f, 3.43f });

	return UPDATE_CONTINUE;
}