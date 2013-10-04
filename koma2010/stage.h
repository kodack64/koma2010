#pragma once

#include "base.h"
#include "fader.h"
#include "map_data.h"

struct ObjectLoc{
	int x;
	int y;
	int k;
};

class Stage{
public:
	int block[MapY][MapX];
	ObjectLoc player;
	ObjectLoc goal;
	int rest;

	virtual int Load(int num);
	virtual int Reset();
};
