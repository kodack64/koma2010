#pragma once

#include "base.h"
#include "map_data.h"

class Map{
private:
	CDirectX* dx;
	Mouse* mouse;
	Key* key;

	int img_block;
	int img_goal;
	int img_coin;
	int block[MapY][MapX];
	b2Body*  bbody[MapY][MapX];
	b2State* bstate[MapY][MapX];

public:
	Map();
	virtual ~Map();
	virtual int Main();
	virtual int Init(CDirectX* cd,Mouse* m,Key* k);
	virtual int Load();
	virtual int Set(int bl[][MapX]);
	virtual int Draw();
	virtual int DrawTile();

	virtual int GetKind(int x,int y);
	virtual int CanGo(int k);
};