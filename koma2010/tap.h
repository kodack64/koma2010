#ifndef PLAY_H
#define PLAY_H

#include "base.h"
#include "fader.h"
#include "stage.h"
#include "tap_data.h"
#include "map.h"
//#include "num.h"
#include "player.h"
#include "goal.h"
#include "movie_data.h"
#include "contact_listener.h"
#include "statbar.h"
#include "splash.h"

class Tap{
private:
	CDirectX* dx;
	Fader fd;
	Mouse* mouse;
	Key* key;

	Stage* stage;
	Map* map;
	Player* player;
	Goal* goal;
	Statbar* statbar;
	Splash* splash;
	b2World* world;
	b2ContactListener* listen; 

	TAP_STATE ts;
	TAP_PLAY_STATE ps;
	MOVIE_STATE ms;
	int stagecount;

	int frame;
	int nextframe;
	bool rb[MAXFRAME];
	int phase;
	int coin;
	int score;
	int rest;
	int shot;
	int totalscore;
	bool regist;
	int MaxStage;
	POINT mp;

	int topscore;
	int rank;
	int playnum;

public:
	Tap();
	virtual ~Tap();
	virtual int Main();
	virtual int Init(CDirectX* cd,Mouse* m,Key* k);
	virtual int Draw();
	virtual int Reset();

	virtual int ProcLoad();
	virtual int ProcPlay();
	virtual int ProcResult();
	virtual int ProcResultDraw();
	virtual int ProcDraw();
	virtual int RegistScore();
};

#endif PLAY_H