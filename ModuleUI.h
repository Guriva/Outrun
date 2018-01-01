#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"

class ModuleUI : public Module
{
public:
	ModuleUI(bool active = true);
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif // __MODULEUI_H__