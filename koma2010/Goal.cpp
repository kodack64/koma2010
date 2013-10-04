#include "goal.h"
#include "box2d_data.h"
Goal::Goal(){
}

Goal::~Goal(){
	SAFE_DELETE(myState);
}

int Goal::Init(CDirectX* cdx){
	dx=cdx;
	dx->SetColorKey(false,0,0,0);
	img_goal=dx->LoadGraph("img/goal.bmp");
	myState= new b2State;
	return 0;
}

int Goal::Draw(){
	b2Vec2 v=myBody->GetPosition();
	v.x*=MtoPIX;
	v.y*=MtoPIX;
//	dx->DrawGraph(v.x,v.y,0,0,0,0,img_goal);
	return 0;
}

int Goal::Set(int x,int y,int k){
	myState->Set(2,0);
	myBody=dx->b2CreateBox(x,y,1,1,0,0,1,0,0,false,true,myState);
	return 0;
}