#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include<vector>
#include "Module.h"

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?
enum CType {
	NONE = -1,
	PLAYER,
	PROP,
	CAR,

	MAX_NUM_COLLIDERS
};

struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	CType colType;
	Module* parent = nullptr;
	// TODO 10: Add a way to notify other classes that a collision happened

	Collider(SDL_Rect rectangle, CType type, Module* parent) : // expand this call if you need to
		rect(rectangle), colType(type), parent(parent)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect, const CType type, Module* parent);
	void DebugDraw();

private:

	std::list<Collider*> colliders;
	bool debug = false;

	bool collisionMatrix[MAX_NUM_COLLIDERS][MAX_NUM_COLLIDERS] = { false, true, true,
																   true, false, false,
																   true, false, false};
};

#endif // __ModuleCollision_H__