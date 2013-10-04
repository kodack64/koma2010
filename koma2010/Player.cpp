#include "player.h"
#include "player_data.h"
#include "physics.h"
#include "physics_player.h"
#include "box2d_data.h"
#include "var.h"

Player::Player(){};

Player::~Player(){
	delete myState;
}

int Player::Main(){
	return 0;
}

int Player::Init(CDirectX *cdx,Mouse* m,Key* k){
	dx=cdx;
	mouse=m;
	key=k;

	myState= new b2State;
	Load();
	return 0;
}

int Player::Load(){
	dx->SetColorKey(true,0,255,0);
	img_player=dx->LoadGraph("img/player.bmp");
	img_arrow=dx->LoadGraph("img/arrow.bmp");
	img_cursor=dx->LoadGraph("img/cursor.bmp");
	wav_shot=dx->LoadWav("wav/shot.wav");
	return 0;
}

int Player::Set(int sx,int sy,int sk){
	ar=0;
	stopcount=0;
	goalcount=0;
	animation=0;
	cursor_r=0;
	myState->Set(0,0);
	px=py=0;
	px=1.0f;
	for(int i=0;i<TRACE;i++){
		trace[i].x=sx+PLAYER_SIZE_X/2;
		trace[i].y=sy+PLAYER_SIZE_Y/2;
	}
	myBody = dx->b2CreateCircle(sx+PLAYER_SIZE_X/2,sy+PLAYER_SIZE_Y/2,PLAYER_SIZE_R,0.5f,0.5f,1.0f,1.0f,0.5f,true,false,myState);
	return 0;
}

int Player::Draw(){
	animation++;
	cursor_r++;
	cursor_r%=360;
	animation%=MaxAnimation*AnimationDiff;
	b2Vec2 v;
	if(!IsAiming()){
		for(int i=1;i<TRACE;i++){
			v=trace[i];
			v.x=v.x*MtoPIX;
			v.y=v.y*MtoPIX;
			dx->SetGraphColor(img_player,1,1,1,0.3-0.1f*i);
//			dx->DrawGraph(v.x-PLAYER_SIZE_X/2,v.y-PLAYER_SIZE_Y/2,PLAYER_SIZE_X,PLAYER_SIZE_Y,IMG_PLAYER_X*(int)(animation/AnimationDiff),0,IMG_PLAYER_X,IMG_PLAYER_Y,myBody->GetAngle()/(2*PI)*360,1,img_player);
		}
	}
	v=myBody->GetPosition();
	v.x=v.x*MtoPIX;
	v.y=v.y*MtoPIX;
	dx->SetGraphColor(img_player,1,1,1,1);
	dx->DrawGraph((v.x-PLAYER_SIZE_X/2)*perc,(v.y-PLAYER_SIZE_Y/2)*perc,PLAYER_SIZE_X,PLAYER_SIZE_Y,IMG_PLAYER_X*(int)(animation/AnimationDiff),0,IMG_PLAYER_X,IMG_PLAYER_Y,myBody->GetAngle()/(2*PI)*360,1.0*perc,img_player);
	if(IsAiming() && !mouse->GetRight()){
	dx->SetSlideDrawScreenCenter(0,0);
		dx->DrawGraph((260-60),(240-60),ARROW_SIZE_X,ARROW_SIZE_Y,0,0,IMG_ARROW_X,IMG_ARROW_Y,ar,1.0f*perc*fabs(px/2 + 0.5),img_arrow);
		dx->DrawGraph((260-60),(int)(240-60+PLAYER_SIZE_Y/2*py*perc),CURSOR_SIZE_X,CURSOR_SIZE_Y,0,0,IMG_CURSOR_X,IMG_CURSOR_Y,cursor_r,(1.3f/4+fabs(sin(cursor_r*2*PI/360)/8)),img_cursor);
	dx->SetSlideDrawScreenCenter((int)(260-GetX()*MtoPIX*perc),(int)(240-GetY()*MtoPIX*perc));
//		dx->DrawGraph((260-ARROW_SIZE_X/2),(240-ARROW_SIZE_Y/2),ARROW_SIZE_X,ARROW_SIZE_Y,0,0,IMG_ARROW_X,IMG_ARROW_Y,ar,1*perc,img_arrow);
//		dx->DrawGraph((v.x*perc-CURSOR_SIZE_X/2+PLAYER_SIZE_X/2*px),(v.y*perc-CURSOR_SIZE_Y/2+PLAYER_SIZE_Y/2*py),CURSOR_SIZE_X,CURSOR_SIZE_Y,0,0,IMG_CURSOR_X,IMG_CURSOR_Y,cursor_r,(1.0f/4+fabs(sin(cursor_r*2*PI/360)/8))*perc,img_cursor);
//		dx->DrawGraph((v.x-ARROW_SIZE_X/2)*perc,(v.y-ARROW_SIZE_Y/2)*perc,ARROW_SIZE_X,ARROW_SIZE_Y,0,0,IMG_ARROW_X,IMG_ARROW_Y,ar,1*perc,img_arrow);
	//	dx->DrawGraph((v.x*perc-CURSOR_SIZE_X/2+PLAYER_SIZE_X/2*px),(v.y*perc-CURSOR_SIZE_Y/2+PLAYER_SIZE_Y/2*py),CURSOR_SIZE_X,CURSOR_SIZE_Y,0,0,IMG_CURSOR_X,IMG_CURSOR_Y,cursor_r,(1.0f/4+fabs(sin(cursor_r*2*PI/360)/8))*perc,img_cursor);
	}
	return 0;
}

bool Player::GoalCheck(){
	return goalcount>GOAL_FRAME;
}

