#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate(float time)
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update(float time)
{
	for (list<Collider*>::const_iterator it = colliders.begin(); it != colliders.cend(); ++it) {
		for (list<Collider*>::const_iterator it2 = next(it); it2 != colliders.cend(); ++it2) {
			CType c = (*it)->colType;
			CType c2 = (*it2)->colType;
			c;
			if ((*it)->CheckCollision((*it2)->rect)) {
				if (collisionMatrix[(*it)->colType][(*it2)->colType]) {
					if ((*it)->parent != nullptr)
						(*it)->parent->OnCollision((*it), (*it2));
				}

				if (collisionMatrix[(*it2)->colType][(*it)->colType]) {
					if ((*it2)->parent != nullptr)
						(*it2)->parent->OnCollision((*it2), (*it));
				}
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if (debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 80);
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}

Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, const CType type, Module* parent)
{
	Collider* ret = new Collider(rect, type, parent);

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	return (rect.x < r.x + r.w && rect.x + rect.w > r.x && rect.y < r.y + r.h && rect.y + rect.h > r.y);
	// TODO 7: Create by hand (avoid consulting the internet) a simple collision test
	// Return true if rectangle argument "r" is intersecting with "this->rect"
}
