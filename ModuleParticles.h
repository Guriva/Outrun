#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"

struct SDL_Texture;

struct Particle
{
	// TODO 1: Fill in the structure with all the properties you need for each particle
	bool to_delete = false;
	iPoint position = { 0, 0 };
	iPoint speed = { 0, 0 };
	Animation anim;
	const char* sound;
	unsigned int fx = 0;
	bool fxPlayed = false;
	unsigned int iniTime = 0;
	unsigned int lifeTime = 0;


	// TODO 11: Add an optional collider to each particle
	Collider* col = nullptr;


	Particle();
	Particle(const Particle& p);
	~Particle();

	void Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status PreUpdate(float time); // clear dirty particles
	update_status Update(float time); // draw
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, CType col_type = NONE); // feel free to expand this call
	void OnCollision(Collider* c1, Collider* c2);

private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> active;

public:
	Particle* prototypeLaser;
	Particle* prototypeExplosion;
	// prototype particles go here ...
};

#endif // __MODULEPARTICLES_H__