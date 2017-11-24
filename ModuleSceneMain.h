#ifndef __MODULESCENEMAIN_H__
#define __MODULESCENEMAIN_H__

#include "Module.h"
#include "Animation.h"

class ModuleSceneMain : public Module
{
public:
	ModuleSceneMain(bool active = true);
	~ModuleSceneMain();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

private:
};

#endif // __MODULESCENEMAIN_H__