#include <math.h>
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

#include "SDL_timer.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	/*graphics = App->textures->Load("rtype/particles.png");


	// TODO 2: Create a prototype for the laser particle
	prototypeLaser = new Particle();
	prototypeLaser->anim.frames.push_back({ 232, 103, 16, 12 });
	prototypeLaser->anim.frames.push_back({ 249, 103, 16, 12 });
	prototypeLaser->anim.speed = 0.1f;
	prototypeLaser->fx = App->audio->LoadFx("rtype/laser.wav");
	prototypeLaser->speed = { 4,0 };
	prototypeLaser->lifeTime = 2000;
	// audio: rtype/laser.wav
	// coords: {232, 103, 16, 12}; {249, 103, 16, 12};


	// TODO 12: Create a new "Explosion" particle
	prototypeExplosion = new Particle();
	prototypeExplosion->anim.frames.push_back({ 274, 296, 33, 30 });
	prototypeExplosion->anim.frames.push_back({ 313, 296, 33, 30 });
	prototypeExplosion->anim.frames.push_back({ 346, 296, 33, 30 });
	prototypeExplosion->anim.frames.push_back({ 382, 296, 33, 30 });
	prototypeExplosion->anim.frames.push_back({ 419, 296, 33, 30 });
	prototypeExplosion->anim.frames.push_back({ 457, 296, 33, 30 });
	prototypeExplosion->anim.speed = 0.1f;
	prototypeExplosion->anim.loop = false;
	prototypeExplosion->fx = App->audio->LoadFx("rtype/explosion.wav");*/
	// audio: rtype/explosion.wav
	// coords: {274, 296, 33, 30}; {313, 296, 33, 30}; {346, 296, 33, 30}; {382, 296, 33, 30}; {419, 296, 33, 30}; {457, 296, 33, 30};

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}

// PreUpdate to clear up all dirty particles
update_status ModuleParticles::PreUpdate(float time)
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

// Update all particle logic and draw them
update_status ModuleParticles::Update(float time)
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
	{
		Particle* p = *it;

		p->Update();
		App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
		if (p->fxPlayed == false) {
			App->audio->PlayFx(p->fx);
			p->fxPlayed = true;
		}
		// Handle particle fx here ?
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, CType col_type)
{
	Particle* p = new Particle(particle);
	p->position.x = x;
	p->position.y = y;
	p->iniTime = SDL_GetTicks();
	if (col_type != NONE)
		p->col = App->collision->AddCollider({ p->position.x,p->position.y,0,0 }, col_type, this);

	active.push_back(p);
	// TODO 4: Fill in a method to create an instance of a prototype particle	
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{}

// TODO 3: Fill in a copy constructor
Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), sound(p.sound), speed(p.speed), col(p.col), fx(p.fx), iniTime(p.iniTime), lifeTime(p.lifeTime)
{
}

Particle::~Particle()
{
}

void Particle::Update()
{
	position.x += speed.x;
	position.y += speed.y;

	//Update particle lifetime
	if (lifeTime > 0) {
		if ((SDL_GetTicks() - iniTime) > lifeTime)
			to_delete = true;
	}
	else {
		if (anim.Finished())
			to_delete = true;
	}
	if (col != nullptr) {
		SDL_Rect r = anim.GetCurrentFrame();
		col->rect = { position.x, position.y, r.w, r.h };
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2) {
	for (list<Particle*>::iterator it = active.begin(); it != active.cend(); ++it) {
		if ((*it)->col == c1) {
			(*it)->to_delete = true;
			/*switch (c1->colType) {
			case LASER:
			App->particles->AddParticle((*App->particles->prototypeExplosion), (*it)->position.x, (*it)->position.y);
			break;
			}*/
		}
	}
}