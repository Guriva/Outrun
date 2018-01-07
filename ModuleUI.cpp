#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "ModuleTextures.h"
#include "ModuleFontManager.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include <string>

ModuleUI::ModuleUI(bool active) : Module(active)
{
	turboRect.reserve(16);

	turboRect.push_back({ 1, 1, 3, 6 });
	turboRect.push_back({ 1, 8, 7, 6 });
	turboRect.push_back({ 1, 15, 11, 6 });
	turboRect.push_back({ 1, 22, 15, 6 });
	turboRect.push_back({ 1, 29, 19, 6 });
	turboRect.push_back({ 1, 36, 23, 6 });
	turboRect.push_back({ 1, 43, 27, 6 });
	turboRect.push_back({ 1, 50, 31, 6 });
	turboRect.push_back({ 1, 57, 35, 6 });
	turboRect.push_back({ 1, 64, 39, 6 });
	turboRect.push_back({ 1, 71, 43, 6 });
	turboRect.push_back({ 1, 78, 47, 6 });
	turboRect.push_back({ 1, 85, 51, 6 });
	turboRect.push_back({ 1, 92, 55, 6 });
	turboRect.push_back({ 1, 99, 59, 6 });
	turboRect.push_back({ 1, 106, 63, 6 });

	gameoverUI = { 1, 77, 71, 14 };
	endUI = { 1, 37, 151, 39 };
	extendPlay.frames.push_back({ 1, 1, 136, 35 });
	extendPlay.frames.push_back({ 138, 1, 136, 35 });
	extendPlay.speed = 0.05f;
}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{
	score = 0;
	gear = 1;
	speed = maxSpeed = turboIndex = 0.f;
	timeLeft = 44.99f;
	lapTime = lastLapTime = totalTime = 0.f;
	checkpointTimer = 4.5f;
	finishTimer = 8.f;
	bonusTime = bonusTimeSub = 0.f;
	checkpoint = savedTime = false;
	uiState = UIInit;
	tick_timer = clock();
	layout = App->textures->Load("Textures/Level/layoutLevel.png");
	turbo = App->textures->Load("Textures/Level/turboBar.png");
	spritesUI = App->textures->Load("Textures/Level/spritesLayout.png");
	App->fonts->loadFont("time", "Textures/Fonts/timeFont.png", "0123456789", 8, 14);
	App->fonts->loadFont("speed", "Textures/Fonts/speedFont.png", "0123456789", 8, 14);
	App->fonts->loadFont("green", "Textures/Fonts/greenFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);
	App->fonts->loadFont("blue", "Textures/Fonts/blueFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ '^", 8, 8);
	App->fonts->loadFont("pink", "Textures/Fonts/pinkFont.png", "0123456789$abcdefghijklmnopqrstuvwxyz.!@ ", 8, 8);

	return true;
}

update_status ModuleUI::Update()
{
	time = (float)((clock() - tick_timer) / (double)CLOCKS_PER_SEC);
	tick_timer = clock();

	int min = (int)(lapTime / 60.f);
	int sec = (int)((int)(lapTime - (float)(min*60)));
	int mili = (int)((int)((lapTime - (int)(lapTime)) * 100.f));
	int secBonus;
	int decBonus;

	gear = App->player->gear + 1;

	switch (uiState)
	{
	case UIInit:
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			if (turboIndex < 16.f)
			{
				turboIndex += time * 20.f;
				if (turboIndex > 16.f)
					turboIndex = 16.f;
			}
		}
		else
		{
			if (turboIndex > 0.f)
			{
				turboIndex -= time * 10.f;
				if (turboIndex < 0.f)
					turboIndex = 0.f;
			}
		}

		break;
	case UIPlay:
		score = App->player->score;
		lapTime += time;
		timeLeft -= time;
		bonusTime = timeLeft;
		bonusTimeSub = bonusTime / 4.f;
		speed = App->player->speed * 1.94f;
		turboIndex = MIN(1.f, (App->player->speed / App->player->maxSpeed)) * 16.f;

		if (checkpoint)
		{
			if (!savedTime)
			{
				lastLapTime = lapTime;
				totalTime += lapTime;
				lapTime = 0.f;
				savedTime = true;
			}

			int min2 = (int)(lastLapTime / 60.f);
			int sec2 = (int)((int)(lastLapTime - (float)(min * 60)));
			int mili2 = (int)((int)((lastLapTime - (int)(lastLapTime)) * 100.f));

			App->renderer->Blit(spritesUI, (int)(SCREEN_WIDTH / 2.f), 300, &(extendPlay.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });

			App->fonts->print(to_string(min2).c_str(), 505, 360, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
			if (sec2 >= 10)
				App->fonts->print(to_string(sec2).c_str(), 580, 360, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
			else
				App->fonts->print(("0" + to_string(sec2)).c_str(), 580, 360, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
			if (mili2 >= 10)
				App->fonts->print(to_string(mili2).c_str(), 655, 360, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
			else
				App->fonts->print(("0" + to_string(mili2)).c_str(), 655, 360, "green", { 3.2f, 3.43f }, { 1.f, 1.f });

			checkpointTimer -= time;
			if (checkpointTimer < 0.f)
			{
				checkpoint = false;
				checkpointTimer = 4.5f;
				savedTime = false;
			}
		}

		break;
	case UIFinish:
		score = App->player->score;
		speed = App->player->speed * 1.94f;
		turboIndex = MIN(1.f, (App->player->speed / App->player->maxSpeed)) * 16.f;
		if (finishTimer < 6.5f && finishTimer >= 1.5f)
		{
			bonusTime -= bonusTimeSub * time;
			if (bonusTime < 0.f)
				bonusTime = 0.f;
			else
				App->player->score += (int)(1000000 * bonusTimeSub * time);
		}

		secBonus = (int)bonusTime;
		decBonus = (int)((bonusTime - (float)secBonus) * 10.f);

		if (finishTimer > 0.f)
		{
			finishTimer -= time;
			App->renderer->Blit(spritesUI, 540, 350, &endUI, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
			App->fonts->print(to_string(secBonus).c_str(), 290, 410, "time", { 3.2f, 3.43f }, { 1.f, 1.f });
			App->fonts->print(to_string(decBonus).c_str(), 340, 410, "time", { 3.2f, 3.43f }, { 1.f, 1.f });
		}

		
		break;
	case UIGameOver:
		App->renderer->Blit(spritesUI, (int)(SCREEN_WIDTH / 2.f), 300, &gameoverUI, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		break;
	}

	App->fonts->print(to_string(min).c_str(), 795, 81, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
	if (sec >= 10)
		App->fonts->print(to_string(sec).c_str(), 870, 81, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
	else
		App->fonts->print(("0" + to_string(sec)).c_str(), 870, 81, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
	if (mili >= 10)
		App->fonts->print(to_string(mili).c_str(), 950, 81, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
	else
		App->fonts->print(("0" + to_string(mili)).c_str(), 950, 81, "green", { 3.2f, 3.43f }, { 1.f, 1.f });

	if (turboIndex >= 1.f)
		App->renderer->Blit(turbo, 90, 760, &turboRect[(int)(turboIndex) - 1], 1.f, { 3.2f, 3.43f }, { 0.f, 1.f });

	App->fonts->print(to_string((int)speed).c_str(), 150, 740, "speed", { 3.2f, 3.43f }, { 1.f, 1.f });
	App->fonts->print(to_string(gear).c_str(), 920, 677, "green", { 3.2f, 3.43f }, { 1.f, 1.f });
	App->fonts->print(to_string((int)timeLeft).c_str(), 235, 81, "time", { 3.2f, 3.43f }, { 1.f, 1.f });
	App->fonts->print(to_string(score).c_str(), 640, 81, "blue", { 3.2f, 3.43f }, { 1.f, 1.f });
	App->renderer->Blit(layout, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2), nullptr, 1.f, { 3.2f, 3.43f }, { 0.5f, 0.5f });

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	App->textures->Unload(layout);
	App->textures->Unload(turbo);
	App->textures->Unload(spritesUI);
	App->fonts->closeFont("time");
	App->fonts->closeFont("speed");
	App->fonts->closeFont("green");
	App->fonts->closeFont("blue");
	App->fonts->closeFont("pink");
	return true;
}