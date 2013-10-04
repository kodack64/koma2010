/*#include "player.h"
#include "player_data.h"
#include "physics_player.h"

int Player::GetRectX(){
	return PLAYER_SIZE_X/2;
}
int Player::GetRectY(){
	return PLAYER_SIZE_Y/2;
}

int Player::DecX(){
	if(fabs(vx)>1){
		if(vx>0)vx-=1;
		else vx+=1;
	}else{
		vx=0;
	}
	vix=round(vx);
	return 0;
}

int Player::DecY(){
	if(fabs(vy)>1){
		if(vy>0)vy-=1;
		else vy+=1;
	}else{
		vy=0;
	}
	viy=round(vy);
	return 0;
}

int Player::DecXY(){
	double vp = hypot(vx,vy);
	if(fabs(vp)>1){
		vx-=vx/vp;
		vy-=vy/vp;
	}else{
		vx=0;
		vy=0;
	}
	vix=round(vx);
	viy=round(vy);
	return 0;
}

int Player::Walk(int a){
	if(a>0){
		Accel(WalkAccel,0);
	}
	if(a<0){
		Accel(-WalkAccel,0);
	}
	return 0;
}

int Player::Dash(int a){
	if(a>0){
		Accel(DashAccel,0);
	}
	if(a<0){
		Accel(-DashAccel,0);
	}
	return 0;
}

int Player::Jump(){
	Accel(0,-JumpAccel);
	return 0;
}
*/