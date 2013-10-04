/*
#include "player.h"
#include "player_data.h"
int Player::Back(int frame){
	x-=rvx[frame];
	y-=rvy[frame];
	return 0;
}

int Player::Next(int frame){
	x+=rvx[frame];
	y+=rvy[frame];
	return 0;
}


int Player::BackReset(){
	int c;
	for(c=0;c<MAXFRAME;c++){
		rvx[c]=0;
		rvy[c]=0;
	}
	return 0;
}
*/