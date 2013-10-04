#ifndef GAME_H
#define	GAME_H

#include	"base.h"
#include	"game_data.h"
#include	"menu.h"
#include	"tap.h"
#include	"map.h"

class	Game:public Base
{
private:
	//ïKê{
	char GameName[MAX_NAME];
	CDirectX	*dx;
	Key key;
	Mouse mouse;

	GAME_STATE gs;
	Menu *menu;
	Tap *tap;
	Map *map;
	int img_allresult;
	int img_font;
	int img_fonts;

public:
	Game();
	virtual ~Game();
	virtual int Main();
	virtual int Draw();
	virtual int Init(CDirectX *p_dx);
	virtual int Reset();
	virtual int ProcMenu();
	virtual int ProcTap();
	virtual int ProcResult();
};

#endif	GAME_H