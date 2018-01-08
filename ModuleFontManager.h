#ifndef __MODULEFONTMANAGER_H__
#define __MODULEFONTMANAGER_H__

#include <list>
#include <map>
#include "Module.h"
#include "Point.h"

using namespace std;

struct SDL_Texture;

struct Font
{
	SDL_Texture* font = nullptr;
	int w;
	int h;
	map<char, int> indexTable;
};

class ModuleFontManager : public Module
{
public:

	ModuleFontManager(bool start_enabled = true);
	~ModuleFontManager();

	bool loadFont(const char* fontName, const char* path, const char* trad, int w, int h);
	void print(const char* text, int posx, int posy, const char* fontName, fPoint scale = { 1, 1 }, fPoint pivot = { 0, 0 });
	int getFontHeight(const char* fontName);
	int getFontWidth(const char* fontName);
	void closeFont(const char* fontName);

	bool CleanUp();

private:
	map<const char*, Font> fontTable;
};

#endif // __MODULEFONTMANAGER_H__