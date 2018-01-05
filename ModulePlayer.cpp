#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "SDL_timer.h"
#include <math.h>

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	preparingAnim.frames.push_back({ 481, 142, 171, 46 });
	preparingAnim.frames.push_back({ 481, 142, 171, 46 });
	preparingAnim.frames.push_back({ 653, 142, 171, 46 });
	preparingAnim.frames.push_back({ 1, 181, 95, 44 });
	preparingAnim.frames.push_back({ 97, 181, 95, 44 });
	preparingAnim.frames.push_back({ 193, 181, 95, 44 });

	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 193, 496, 95, 44 });
	crash1.frames.push_back({ 481, 283, 95, 52 });
	crash1.frames.push_back({ 481, 283, 95, 52 });
	crash1.frames.push_back({ 577, 283, 95, 52 });
	crash1.frames.push_back({ 577, 283, 95, 52 });
	crash1.frames.push_back({ 481, 283, 95, 52 });
	crash1.frames.push_back({ 481, 283, 95, 52 });
	crash1.frames.push_back({ 577, 283, 95, 52 });
	crash1.frames.push_back({ 577, 283, 95, 52 });

	crash2.frames.push_back({ 653, 142, 171, 46 });
	crash2.frames.push_back({ 481, 142, 171, 46 });
	crash2.frames.push_back({ 653, 95, 171, 46 });
	crash2.frames.push_back({ 481, 95, 171, 46 });
	crash2.frames.push_back({ 653, 48, 171, 46 });
	crash2.frames.push_back({ 481, 48, 171, 46 });
	crash2.frames.push_back({ 653, 1, 171, 46 });
	crash2.frames.push_back({ 481, 1, 171, 46 });
	crash2.frames.push_back({ 653, 142, 171, 46 });
	crash2.frames.push_back({ 653, 142, 171, 46 });
	crash2.frames.push_back({ 653, 142, 171, 46 });
	crash2.frames.push_back({ 481, 236, 171, 46 });
	crash2.frames.push_back({ 481, 236, 171, 46 });
	crash2.frames.push_back({ 653, 236, 171, 46 });
	crash2.frames.push_back({ 653, 236, 171, 46 });
	crash2.frames.push_back({ 481, 236, 171, 46 });
	crash2.frames.push_back({ 481, 236, 171, 46 });
	crash2.frames.push_back({ 653, 236, 171, 46 });
	crash2.frames.push_back({ 653, 236, 171, 46 });

	crash21.frames.push_back({ 653, 142, 171, 46 });
	crash21.frames.push_back({ 481, 142, 171, 46 });
	crash21.frames.push_back({ 653, 95, 171, 46 });
	crash21.frames.push_back({ 481, 95, 171, 46 });
	crash21.frames.push_back({ 653, 48, 171, 46 });
	crash21.frames.push_back({ 481, 48, 171, 46 });
	crash21.frames.push_back({ 653, 1, 171, 46 });
	crash21.frames.push_back({ 481, 1, 171, 46 });
	crash21.frames.push_back({ 653, 142, 171, 46 });
	crash21.frames.push_back({ 481, 142, 171, 46 });
	crash21.frames.push_back({ 653, 95, 171, 46 });
	crash21.frames.push_back({ 481, 95, 171, 46 });
	crash21.frames.push_back({ 653, 48, 171, 46 });
	crash21.frames.push_back({ 481, 48, 171, 46 });
	crash21.frames.push_back({ 653, 1, 171, 46 });
	crash21.frames.push_back({ 481, 1, 171, 46 });
	crash21.frames.push_back({ 653, 142, 171, 46 });
	crash21.frames.push_back({ 653, 142, 171, 46 });
	crash21.frames.push_back({ 653, 142, 171, 46 });
	crash21.frames.push_back({ 481, 236, 171, 46 });
	crash21.frames.push_back({ 481, 236, 171, 46 });
	crash21.frames.push_back({ 653, 236, 171, 46 });
	crash21.frames.push_back({ 653, 236, 171, 46 });
	crash21.frames.push_back({ 481, 236, 171, 46 });
	crash21.frames.push_back({ 481, 236, 171, 46 });
	crash21.frames.push_back({ 653, 236, 171, 46 });
	crash21.frames.push_back({ 653, 236, 171, 46 });

	endSequence.frames.push_back({ 193, 181, 95, 44 });
	endSequence.frames.push_back({ 193, 271, 95, 44 });
	endSequence.frames.push_back({ 193, 181, 95, 44 });
	endSequence.frames.push_back({ 193, 271, 95, 44 });
	endSequence.frames.push_back({ 193, 181, 95, 44 });
	endSequence.frames.push_back({ 193, 271, 95, 44 });
	endSequence.frames.push_back({ 193, 181, 95, 44 });
	endSequence.frames.push_back({ 193, 271, 95, 44 });
	endSequence.frames.push_back({ 97, 181, 95, 44 });
	endSequence.frames.push_back({ 97, 271, 95, 44 });
	endSequence.frames.push_back({ 1, 181, 95, 44 });
	endSequence.frames.push_back({ 1, 271, 95, 44 });
	for (int i = 0; i < 25; ++i)
		endSequence.frames.push_back({ 481, 142, 171, 46 });
	

	carSmokeL.frames.push_back({ 1, 1, 58, 17 });
	carSmokeL.frames.push_back({ 60, 1, 58, 17 });
	carSmokeL.frames.push_back({ 119, 1, 58, 17 });
	carSmokeL.frames.push_back({ 178, 1, 58, 17 });
	carSmokeL.speed = 0.2f;

	carSmokeR.frames.push_back({ 414, 1, 58, 17 });
	carSmokeR.frames.push_back({ 355, 1, 58, 17 });
	carSmokeR.frames.push_back({ 296, 1, 58, 17 });
	carSmokeR.frames.push_back({ 237, 1, 58, 17 });
	carSmokeR.speed = 0.2f;

	carSandL.frames.push_back({ 1, 19, 68, 42 });
	carSandL.frames.push_back({ 70, 19, 68, 42 });
	carSandL.frames.push_back({ 139, 19, 68, 42 });
	carSandL.frames.push_back({ 208, 19, 68, 42});
	carSandL.speed = 0.2f;

	carSandR.frames.push_back({ 484, 19, 68, 42 });
	carSandR.frames.push_back({ 415, 19, 68, 42});
	carSandR.frames.push_back({ 346, 19, 68, 42 });
	carSandR.frames.push_back({ 277, 19, 68, 42 });
	carSandR.speed = 0.2f;

	straight.frames.push_back({ 193, 181, 95, 44 });
	straight.frames.push_back({ 193, 271, 95, 44 });
	straight.frames.push_back({ 193, 181, 95, 44 });
	straight.frames.push_back({ 193, 271, 95, 44 });
	straight.frames.push_back({ 193, 226, 95, 44 });
	straight.frames.push_back({ 193, 316, 95, 44 });
	straight.frames.push_back({ 193, 226, 95, 44 });
	straight.frames.push_back({ 193, 316, 95, 44 });
	straight.speed = 0.f;

	straightleft.frames.push_back({ 97, 181, 95, 44 });
	straightleft.frames.push_back({ 97, 271, 95, 44 });
	straightleft.frames.push_back({ 97, 181, 95, 44 });
	straightleft.frames.push_back({ 97, 271, 95, 44 });
	straightleft.frames.push_back({ 97, 226, 95, 44 });
	straightleft.frames.push_back({ 97, 316, 95, 44 });
	straightleft.frames.push_back({ 97, 226, 95, 44 });
	straightleft.frames.push_back({ 97, 316, 95, 44 });
	straightleft.speed = 0.f;

	straightleftMost.frames.push_back({ 1, 181, 95, 44 });
	straightleftMost.frames.push_back({ 1, 271, 95, 44 });
	straightleftMost.frames.push_back({ 1, 181, 95, 44 });
	straightleftMost.frames.push_back({ 1, 271, 95, 44 });
	straightleftMost.frames.push_back({ 1, 226, 95, 44 });
	straightleftMost.frames.push_back({ 1, 316, 95, 44 });
	straightleftMost.frames.push_back({ 1, 226, 95, 44 });
	straightleftMost.frames.push_back({ 1, 316, 95, 44 });
	straightleftMost.speed = 0.f;

	straightright.frames.push_back({ 289, 181, 95, 44 });
	straightright.frames.push_back({ 289, 271, 95, 44 });
	straightright.frames.push_back({ 289, 181, 95, 44 });
	straightright.frames.push_back({ 289, 271, 95, 44 });
	straightright.frames.push_back({ 289, 226, 95, 44 });
	straightright.frames.push_back({ 289, 316, 95, 44 });
	straightright.frames.push_back({ 289, 226, 95, 44 });
	straightright.frames.push_back({ 289, 316, 95, 44 });
	straightright.speed = 0.f;

	straightrightMost.frames.push_back({ 385, 181, 95, 44 });
	straightrightMost.frames.push_back({ 385, 271, 95, 44 });
	straightrightMost.frames.push_back({ 385, 181, 95, 44 });
	straightrightMost.frames.push_back({ 385, 271, 95, 44 });
	straightrightMost.frames.push_back({ 385, 226, 95, 44 });
	straightrightMost.frames.push_back({ 385, 316, 95, 44 });
	straightrightMost.frames.push_back({ 385, 226, 95, 44 });
	straightrightMost.frames.push_back({ 385, 316, 95, 44 });
	straightrightMost.speed = 0.f;

	up.frames.push_back({ 193, 1, 95, 44 });
	up.frames.push_back({ 193, 91, 95, 44 });
	up.frames.push_back({ 193, 1, 95, 44 });
	up.frames.push_back({ 193, 91, 95, 44 });
	up.frames.push_back({ 193, 46, 95, 44 });
	up.frames.push_back({ 193, 136, 95, 44 });
	up.frames.push_back({ 193, 46, 95, 44 });
	up.frames.push_back({ 193, 136, 95, 44 });
	up.speed = 0.f;

	upleft.frames.push_back({ 97, 1, 95, 44 });
	upleft.frames.push_back({ 97, 91, 95, 44 });
	upleft.frames.push_back({ 97, 1, 95, 44 });
	upleft.frames.push_back({ 97, 91, 95, 44 });
	upleft.frames.push_back({ 97, 46, 95, 44 });
	upleft.frames.push_back({ 97, 136, 95, 44 });
	upleft.frames.push_back({ 97, 46, 95, 44 });
	upleft.frames.push_back({ 97, 136, 95, 44 });
	upleft.speed = 0.f;

	upleftMost.frames.push_back({ 1, 1, 95, 44 });
	upleftMost.frames.push_back({ 1, 91, 95, 44 });
	upleftMost.frames.push_back({ 1, 1, 95, 44 });
	upleftMost.frames.push_back({ 1, 91, 95, 44 });
	upleftMost.frames.push_back({ 1, 46, 95, 44 });
	upleftMost.frames.push_back({ 1, 136, 95, 44 });
	upleftMost.frames.push_back({ 1, 46, 95, 44 });
	upleftMost.frames.push_back({ 1, 136, 95, 44 });
	upleftMost.speed = 0.f;

	upright.frames.push_back({ 289, 1, 95, 44 });
	upright.frames.push_back({ 289, 91, 95, 44 });
	upright.frames.push_back({ 289, 1, 95, 44 });
	upright.frames.push_back({ 289, 91, 95, 44 });
	upright.frames.push_back({ 289, 46, 95, 44 });
	upright.frames.push_back({ 289, 136, 95, 44 });
	upright.frames.push_back({ 289, 46, 95, 44 });
	upright.frames.push_back({ 289, 136, 95, 44 });
	upright.speed = 0.f;

	uprightMost.frames.push_back({ 385, 1, 95, 44 });
	uprightMost.frames.push_back({ 385, 91, 95, 44 });
	uprightMost.frames.push_back({ 385, 1, 95, 44 });
	uprightMost.frames.push_back({ 385, 91, 95, 44 });
	uprightMost.frames.push_back({ 385, 46, 95, 44 });
	uprightMost.frames.push_back({ 385, 136, 95, 44 });
	uprightMost.frames.push_back({ 385, 46, 95, 44 });
	uprightMost.frames.push_back({ 385, 136, 95, 44 });
	uprightMost.speed = 0.f;

	down.frames.push_back({ 193, 361, 95, 44 });
	down.frames.push_back({ 193, 451, 95, 44 });
	down.frames.push_back({ 193, 361, 95, 44 });
	down.frames.push_back({ 193, 451, 95, 44 });
	down.frames.push_back({ 193, 406, 95, 44 });
	down.frames.push_back({ 193, 496, 95, 44 });
	down.frames.push_back({ 193, 406, 95, 44 });
	down.frames.push_back({ 193, 496, 95, 44 });
	down.speed = 0.f;

	downleft.frames.push_back({ 97, 361, 95, 44 });
	downleft.frames.push_back({ 97, 451, 95, 44 });
	downleft.frames.push_back({ 97, 361, 95, 44 });
	downleft.frames.push_back({ 97, 451, 95, 44 });
	downleft.frames.push_back({ 97, 406, 95, 44 });
	downleft.frames.push_back({ 97, 496, 95, 44 });
	downleft.frames.push_back({ 97, 406, 95, 44 });
	downleft.frames.push_back({ 97, 496, 95, 44 });
	downleft.speed = 0.f;

	downleftMost.frames.push_back({ 1, 361, 95, 44 });
	downleftMost.frames.push_back({ 1, 451, 95, 44 });
	downleftMost.frames.push_back({ 1, 361, 95, 44 });
	downleftMost.frames.push_back({ 1, 451, 95, 44 });
	downleftMost.frames.push_back({ 1, 406, 95, 44 });
	downleftMost.frames.push_back({ 1, 496, 95, 44 });
	downleftMost.frames.push_back({ 1, 406, 95, 44 });
	downleftMost.frames.push_back({ 1, 496, 95, 44 });
	downleftMost.speed = 0.f;

	downright.frames.push_back({ 289, 361, 95, 44 });
	downright.frames.push_back({ 289, 451, 95, 44 });
	downright.frames.push_back({ 289, 361, 95, 44 });
	downright.frames.push_back({ 289, 451, 95, 44 });
	downright.frames.push_back({ 289, 406, 95, 44 });
	downright.frames.push_back({ 289, 496, 95, 44 });
	downright.frames.push_back({ 289, 406, 95, 44 });
	downright.frames.push_back({ 289, 496, 95, 44 });
	downright.speed = 0.f;

	downrightMost.frames.push_back({ 385, 361, 95, 44 });
	downrightMost.frames.push_back({ 385, 451, 95, 44 });
	downrightMost.frames.push_back({ 385, 361, 95, 44 });
	downrightMost.frames.push_back({ 385, 451, 95, 44 });
	downrightMost.frames.push_back({ 385, 406, 95, 44 });
	downrightMost.frames.push_back({ 385, 496, 95, 44 });
	downrightMost.frames.push_back({ 385, 406, 95, 44 });
	downrightMost.frames.push_back({ 385, 496, 95, 44 });
	downrightMost.speed = 0.f;

	carStates[UP][LEFTMOST] = &upleftMost;
	carStates[UP][LEFT] = &upleft;
	carStates[UP][FRONT] = &up;
	carStates[UP][RIGHT] = &upright;
	carStates[UP][RIGHTMOST] = &uprightMost;
	carStates[STRAIGHT][LEFTMOST] = &straightleftMost;
	carStates[STRAIGHT][LEFT] = &straightleft;
	carStates[STRAIGHT][FRONT] = &straight;
	carStates[STRAIGHT][RIGHT] = &straightright;
	carStates[STRAIGHT][RIGHTMOST] = &straightrightMost;
	carStates[DOWN][LEFTMOST] = &downleftMost;
	carStates[DOWN][LEFT] = &downleft;
	carStates[DOWN][FRONT] = &down;
	carStates[DOWN][RIGHT] = &downright;
	carStates[DOWN][RIGHTMOST] = &downrightMost;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	tick_timer = clock();
	inclination = STRAIGHT;
	direction = FRONT;
	playerState = PREPARING;
	wheelL = wheelR = NORMAL;
	speed = 0.f;
	highAccel = 10.f;
	thresholdX = 1.f;
	varThresholdX = 0.06f;
	offsetCrash1 = 0.f;
	maxSpeed = 100.f;
	lowAccel = maxSpeed / 6.5f;
	forceX = 0.3f;
	prepPos = 7.29f;
	sinDif = 0.f;
	prepPosAct = 0.f;
	score = 0;
	lastSlide = 0.2f;
	current_animation = &preparingAnim;
	gear = false;
	speedSoundAct = slideSoundAct = false;

	preparingAnim.loop = false;
	preparingAnim.speed = 0.f;
	preparingAnim.Reset();
	preparingAnim.ResetLoops();
	crash1.loop = false;
	crash1.speed = 0.2f;
	crash1.Reset();
	crash1.ResetLoops();
	crash2.loop = false;
	crash2.speed = 0.2f;
	crash2.Reset();
	crash2.ResetLoops();
	crash21.loop = false;
	crash21.speed = 0.2f;
	crash21.Reset();
	crash21.ResetLoops();
	endSequence.loop = false;
	endSequence.speed = 0.12f;
	endSequence.Reset();
	endSequence.ResetLoops();

	car = App->textures->Load("Textures/Level/ferrari.png");
	carEffects = App->textures->Load("Textures/Level/effectsCar.png");
	speedSound = App->audio->LoadFx("Audio/turboCar.wav");
	slideSound = App->audio->LoadFx("Audio/slide.wav");

	//App->audio->PlayFx(slideSound, -1);
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	time = (float)((clock() - tick_timer) / (double)CLOCKS_PER_SEC);
	tick_timer = clock();
	switch (playerState)
	{
	case PREPARING:
		UpdatePlayerPreparing();
		break;
	case ONROAD:
		UpdatePlayerOnRoad();
		break;
	case SMALLCOLLISION:
		UpdatePlayerSCol();
		break;
	case MEDIUMCOLLISION:
		UpdatePlayerMCol();
		break;
	case AUTO:
		UpdatePlayerAuto();
		break;
	case PlayerGAMEOVER:
		App->audio->StopFxChannel(1);
		App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 5, (int)(SCREEN_HEIGHT / 2) + 304, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f,3.43f }, { 0.5f,0.5f });
		break;
	case ENDING:
		UpdatePlayerEnding();
		break;
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::UpdatePlayerPreparing()
{
	if (preparingAnim.speed > 0.f)
	{
		if (sinDif < 180)
		{
			sinDif += time * 200.f;
			if (sinDif > 180)
				sinDif = 180;
		}
		prepPosAct += prepPos*sin(sinDif*(float)M_PI / 180.f);
		App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 255 - (int)prepPosAct, (int)(SCREEN_HEIGHT / 2) + 304, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
		if (sinDif > 0.f && sinDif < 180.f)
		{
			App->renderer->Blit(carEffects, (int)(SCREEN_WIDTH / 2) + 280 - (int)prepPosAct, (int)(SCREEN_HEIGHT / 2) + 380, &(carSmokeR.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.f, 1.f });
			App->renderer->Blit(carEffects, (int)(SCREEN_WIDTH / 2) + 230 - (int)prepPosAct, (int)(SCREEN_HEIGHT / 2) + 380, &(carSmokeR.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 1.f, 1.f });
		}
	}
	else
	{
		App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 255, (int)(SCREEN_HEIGHT / 2) + 304, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f, 3.43f }, { 0.5f, 0.5f });
	}
}

void ModulePlayer::UpdatePlayerOnRoad()
{
	if (wheelL == SAND && wheelR == SAND)
		maxSpeed = 75.f;
	else
	{
		if (gear)
			maxSpeed = (int)SEGMENT_LENGTH;
		else
			maxSpeed = 100.f;
	}

	//Check input for speed
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && speed < maxSpeed)
	{
		speed += lowAccel * time;
		if (speed > maxSpeed)
			speed = maxSpeed;
	}
	//Decelerate when changing car gear
	if (speed > maxSpeed)
		speed -= lowAccel * time;
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && speed > 0.f)
	{
		speed -= 3 * lowAccel * time;
		if (speed < 0.f)
			speed = 0.f;
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_IDLE && speed > 0.f)
	{
		speed -= lowAccel * time;
		if (speed < 0.f)
			speed = 0.f;
	}
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		gear = !gear;
		if (gear)
			maxSpeed = (int)SEGMENT_LENGTH;
		else
			maxSpeed = 100.f;
	}

	//Check input for side
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (thresholdX > 0.f)
			thresholdX -= varThresholdX;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (thresholdX < 2.f)
			thresholdX += varThresholdX;
	}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
	{
		if (thresholdX < 1.f)
			thresholdX += varThresholdX;
		else if (thresholdX > 1.f)
			thresholdX -= varThresholdX;
		else if (thresholdX != 1.f && thresholdX > 0.95f && thresholdX < 1.05f)
			thresholdX = 1.f;
	}

	//Change speed of wheels depending on car speed
	if (speed > 0.f && speed < maxSpeed / 2)
	{
		for (int i = 0; i < MAXINCL; ++i)
		{
			for (int j = 0; j < MAXDIR; ++j)
				carStates[i][j]->speed = 0.1f;
		}
	}
	else if (speed > maxSpeed / 2)
	{
		for (int i = 0; i < MAXINCL; ++i)
		{
			for (int j = 0; j < MAXDIR; ++j)
				carStates[i][j]->speed = 0.25f;
		}
	}
	else
	{
		for (int i = 0; i < MAXINCL; ++i)
		{
			for (int j = 0; j < MAXDIR; ++j)
				carStates[i][j]->speed = 0.f;
		}
	}

	//Animation change
	if (thresholdX < 0.4f && speed > 1.0f && direction != LEFTMOST)
		direction = LEFTMOST;
	if (thresholdX > 0.4f && speed > 1.0f && thresholdX < 0.8f && direction != LEFT)
		direction = LEFT;
	if ((thresholdX > 0.8f && thresholdX < 1.2f && direction != FRONT) || speed <= 1.0f)
		direction = FRONT;
	if (thresholdX > 1.2f && speed > 1.0f && thresholdX < 1.6f && direction != RIGHT)
		direction = RIGHT;
	if (thresholdX > 1.6f && speed > 1.0f && direction != RIGHTMOST)
		direction = RIGHTMOST;

	current_animation = carStates[inclination][direction];

	App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 5, (int)(SCREEN_HEIGHT / 2) + 304, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f,3.43f }, { 0.5f,0.5f });
	CheckWheels();

	//Player only scores if in road
	if (wheelL != SAND && wheelR != SAND && speed > 5.f)
		score += (int)((10.f + 950.f * ((speed - 5.f) / (145.f))) / 10.f) * 10;
}

void ModulePlayer::UpdatePlayerSCol()
{
	speed = 0.f;
	if (offsetCrash1 < 1.f)
		offsetCrash1 += 0.03f;

	if (!current_animation->Finished())
		App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 5, (int)(SCREEN_HEIGHT / 2) + 304 - sin((float)(offsetCrash1*M_PI)) * 12, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f,3.43f }, { 0.5f,0.5f });
	CheckWheels();
}

void ModulePlayer::UpdatePlayerMCol()
{
	
	if (speed > 0.f)
	{
		speed -= lowAccel * time;
		if (speed < 0.f)
			speed = 0.f;
	}
	if (!current_animation->Finished())
		App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 5, (int)(SCREEN_HEIGHT / 2) + 304, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f,3.43f }, { 0.5f,0.5f });
	CheckWheels();
}

void ModulePlayer::UpdatePlayerAuto()
{
	//Player at maximum speed
	if (!gear) gear = true;
	maxSpeed = (int)SEGMENT_LENGTH;
	speed += lowAccel * time;
	if (speed > maxSpeed)
		speed = maxSpeed;

	wheelL = wheelR = NORMAL;
	current_animation = carStates[STRAIGHT][FRONT];
	if (speed > 5.f)
		score += (int)((10.f + 950.f * ((speed - 5.f) / (145.f))) / 10.f) * 10;

	App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 5, (int)(SCREEN_HEIGHT / 2) + 304, &(current_animation->GetCurrentFrame()), 1.0f, { 3.2f,3.43f }, { 0.5f,0.5f });
	//CheckWheels();
}

void ModulePlayer::UpdatePlayerEnding()
{
	if (speed > 0.f)
	{
		speed -= lowAccel * time * 3.f;
		if (speed < 0.f)
			speed = 0.f;
	}
	else
		wheelL = wheelR = NORMAL;

	App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2) + 5, (int)(SCREEN_HEIGHT / 2) + 304, &(endSequence.GetCurrentFrame()), 1.0f, { 3.2f,3.43f }, { 0.5f,0.5f });
	CheckWheels();
}

void ModulePlayer::CheckWheels()
{
	if (playerState == ONROAD)
	{
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && !gear && speed < 50 && wheelL != SAND && wheelR != SAND)
			wheelR = SMOKE;
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && !gear && speed < 50 && wheelR != SAND && wheelL != SAND)
			wheelL = SMOKE;
	}
	else
	{
		if (speed > 0 && wheelL != SAND && wheelR != SAND)
			wheelR = SMOKE;
		if (speed > 0 && wheelR != SAND && wheelL != SAND)
			wheelL = SMOKE;
	}

	switch (wheelR)
	{
	case SMOKE:
		App->renderer->Blit(carEffects, (int)(SCREEN_WIDTH / 2) + 30, (int)(SCREEN_HEIGHT / 2) + 380, &(carSmokeR.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.f, 1.f});
		break;
	case SAND:
		App->renderer->Blit(carEffects, (int)(SCREEN_WIDTH / 2) + 30, (int)(SCREEN_HEIGHT / 2) + 380, &(carSandR.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 0.f, 1.f });
		break;
	}
	switch (wheelL)
	{
	case SMOKE:
		App->renderer->Blit(carEffects, (int)(SCREEN_WIDTH / 2) - 20, (int)(SCREEN_HEIGHT / 2) + 380, &(carSmokeL.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 1.f, 1.f });
		break;
	case SAND:
		App->renderer->Blit(carEffects, (int)(SCREEN_WIDTH / 2) - 20, (int)(SCREEN_HEIGHT / 2) + 380, &(carSandL.GetCurrentFrame()), 1.f, { 3.2f, 3.43f }, { 1.f, 1.f });
		break;
	}

	if ((wheelL == SMOKE || wheelR == SMOKE))
	{
		if (!slideSoundAct && lastSlide > 0.1f)
		{
			slideSoundAct = true;
			App->audio->PlayFxChannel(slideSound, -1, 1);
		}
		lastSlide = 0.f;
	}
	else
	{
		lastSlide += time;
		if (lastSlide > 0.1f && slideSoundAct)
		{
			slideSoundAct = false;
			App->audio->StopFxChannel(1);
		}
	}
		
}

void ModulePlayer::resetCounters()
{
	offsetCrash1 = 0.f;
}