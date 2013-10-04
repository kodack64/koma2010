#ifndef MENU_H
#define MENU_H

#include "base.h"
#include "fader.h"

class Menu{
private:
	CDirectX* dx;
	Fader fd;
	Mouse* mouse;
	Key* key;

	int img_menu;
	int img_block;

	int dec;

public:
	Menu();
	virtual ~Menu();
	virtual int Main();
	virtual int Init(CDirectX* cd,Mouse* m,Key* k);
	virtual int Load();
	virtual int Draw();
	virtual int Reset();
};

#endif MENU_H