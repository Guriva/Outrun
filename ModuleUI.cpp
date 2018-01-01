#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"

ModuleUI::ModuleUI(bool active) : Module(active)
{

}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{
	return true;
}

update_status ModuleUI::Update()
{
	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	return true;
}