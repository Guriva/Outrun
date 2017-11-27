#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "SDL_timer.h"
#include <math.h>

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	inclination = STRAIGHT;
	direction = FRONT;
	speed = 0.f;
	lowAccel = 0.05f;
	highAccel = 10.f;
	thresholdX = 1.f;
	varThresholdX = 0.06f;
	xPos = 0.f;
	xSpeed = 0.f;
	maxSpeed = 10.f;

	straight.frames.push_back({ 165, 91, 81, 44 });
	straight.frames.push_back({ 165, 136, 81, 44 });
	straight.speed = 0.f;

	straightleft.frames.push_back({ 83, 91, 81, 44 });
	straightleft.frames.push_back({ 83, 136, 81, 44 });
	straightleft.speed = 0.f;

	straightleftMost.frames.push_back({ 1, 91, 81, 44 });
	straightleftMost.frames.push_back({ 1, 136, 81, 44 });
	straightleftMost.speed = 0.f;

	straightright.frames.push_back({ 247, 91, 81, 44 });
	straightright.frames.push_back({ 247, 136, 81, 44 });
	straightright.speed = 0.f;

	straightrightMost.frames.push_back({ 329, 91, 81, 44 });
	straightrightMost.frames.push_back({ 329, 136, 81, 44 });
	straightrightMost.speed = 0.f;

	up.frames.push_back({ 165, 1, 81, 44 });
	up.frames.push_back({ 165, 46, 81, 44 });
	up.speed = 0.f;

	upleft.frames.push_back({ 83, 1, 81, 44 });
	upleft.frames.push_back({ 83, 46, 81, 44 });
	upleft.speed = 0.f;

	upleftMost.frames.push_back({ 1, 1, 81, 44 });
	upleftMost.frames.push_back({ 1, 46, 81, 44 });
	upleftMost.speed = 0.f;

	upright.frames.push_back({ 247, 1, 81, 44 });
	upright.frames.push_back({ 247, 46, 81, 44 });
	upright.speed = 0.f;

	uprightMost.frames.push_back({ 329, 1, 81, 44 });
	uprightMost.frames.push_back({ 329, 46, 81, 44 });
	uprightMost.speed = 0.f;

	down.frames.push_back({ 165, 181, 81, 44 });
	down.frames.push_back({ 165, 226, 81, 44 });
	down.speed = 0.f;

	downleft.frames.push_back({ 83, 181, 81, 44 });
	downleft.frames.push_back({ 83, 226, 81, 44 });
	downleft.speed = 0.f;

	downleftMost.frames.push_back({ 1, 181, 81, 44 });
	downleftMost.frames.push_back({ 1, 226, 81, 44 });
	downleftMost.speed = 0.f;

	downright.frames.push_back({ 247, 181, 81, 44 });
	downright.frames.push_back({ 247, 226, 81, 44 });
	downright.speed = 0.f;

	downrightMost.frames.push_back({ 329, 181, 81, 44 });
	downrightMost.frames.push_back({ 329, 226, 81, 44 });
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

	car = App->textures->Load("Textures/Level/ferrari.png");

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
	//Check input for speed
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && speed < maxSpeed)
		speed += lowAccel;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_IDLE && speed > 0.f) {
		speed -= lowAccel;
		if (speed < 0.f)
			speed = 0.f;
	}

	//Check input for side
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		if (xSpeed > -0.01f)
			xSpeed -= 0.001f;
		if (thresholdX > 0.f)
			thresholdX -= varThresholdX;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		if (xSpeed < 0.01f)
			xSpeed += 0.001f;
		if (thresholdX < 2.f)
			thresholdX += varThresholdX;
	}
	
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_IDLE)
	{
		if (xSpeed < 0.f)
		{
			xSpeed += 0.001f;
			if (xSpeed > 0.f)
				xSpeed = 0.f;
		}
		else if (xSpeed > 0.f)
		{
			xSpeed -= 0.001f;
			if (xSpeed < 0.f)
				xSpeed = 0.f;
		}
		if (thresholdX < 1.f)
			thresholdX += varThresholdX;
		else if (thresholdX > 1.f)
			thresholdX -= varThresholdX;
		else if (thresholdX != 1.f && thresholdX > 0.95f && thresholdX < 1.05f)
			thresholdX = 1.f;
	}

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
	
	//Change xPos of car
	xPos += xSpeed;

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

	App->renderer->Blit(car, (int)(SCREEN_WIDTH / 2), (int)(SCREEN_HEIGHT / 2) + 90, &(current_animation->GetCurrentFrame()), 1.0f, { 1,1 }, {0.5f,0.5f});

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{}
