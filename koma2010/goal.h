#pragma once

#include "base.h"
#include "frame.h"

class Goal{
private:
	CDirectX* dx;
	int img_goal;
	b2Body* myBody;
	b2State* myState;
	int animation;
public:
	Goal();
	virtual ~Goal();
	virtual int Init(CDirectX* cd);
	virtual int Draw();
	virtual int Set(int x,int y,int k);
	b2Body* GetBody(){return myBody;};
};