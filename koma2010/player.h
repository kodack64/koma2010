#pragma once

#include "base.h"
#include "frame.h"

#define TRACE 10

class Player{
private:
	CDirectX* dx;
	Mouse* mouse;
	Key* key;

	int img_player;
	int img_arrow;
	int img_cursor;
	int wav_shot;
	double ar;
	float px;
	float py;

	b2Body* myBody;
	b2State* myState;
	b2Vec2 trace[TRACE];
	int animation;
	int cursor_r;
	int stopcount;
	int goalcount;

public:
	Player();
	virtual ~Player();
	virtual int Main();
	virtual int Init(CDirectX* cd,Mouse* m,Key* k);
	virtual int Load();
	virtual int Draw();

	virtual int Aiming();
	virtual int Shot();
	virtual int Traceup();
	virtual int Set(int x,int y,int k);
	virtual bool IsStop();
	virtual bool IsAiming();

	float GetX(){return myBody->GetPosition().x;};
	float GetY(){return myBody->GetPosition().y;};
	float GetPx(){return px;};
	float GetPy(){return py;};
	b2Body* GetBody(){return myBody;};
	void GoalInside(){goalcount++;};
	void GoalOutside(){goalcount=0;};
	virtual bool GoalCheck();

};