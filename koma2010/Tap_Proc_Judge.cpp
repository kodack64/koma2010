/*
#include "tap.h"

int Tap::Judge(){
	//player - enemy
	if(false){
//		player->Die();
	}

	//player - map
	int gk,xdirection,ydirection;

	xdirection=0;
	if(player->GetVecX()>0){
		xdirection=1;
	}else if(player->GetVecX()<0){
		xdirection=-1;
	}
	if(xdirection!=0){
		gk=map->GetKind(player->GetMoveX() + xdirection*player->GetRectX() ,player->GetStopY()  + player->GetRectY() ) ;
		while(!map->CanGo( gk ))
		{
			if(player->GetVecX()==0){
				assert(false);
				break;
			}
			player->DecX();
			gk=map->GetKind(player->GetMoveX() + xdirection*player->GetRectX() ,player->GetStopY()  + player->GetRectY() ) ;
		}
		gk=map->GetKind(player->GetMoveX() + xdirection*player->GetRectX() ,player->GetStopY()  - player->GetRectY() ) ;
		while(!map->CanGo( gk ))
		{
			if(player->GetVecX()==0){
				assert(false);
				break;
			}
			player->DecX();
			gk=map->GetKind(player->GetMoveX() + xdirection*player->GetRectX() ,player->GetStopY()  - player->GetRectY() ) ;
		}
	}

	ydirection=0;
	if(player->GetVecY()>0){
		ydirection=1;
	}if(player->GetVecY()<0){
		ydirection=-1;
	}
	if(ydirection!=0){
		gk=map->GetKind(player->GetStopX() + player->GetRectX() ,player->GetMoveY() + ydirection* player->GetRectY() ) ;
		while(!map->CanGo( gk ))
		{
			if(player->GetVecY()==0){
				assert(false);
				break;
			}
			player->DecY();
			gk=map->GetKind(player->GetStopX() + player->GetRectX() ,player->GetMoveY() + ydirection* player->GetRectY() ) ;
		}
		gk=map->GetKind(player->GetStopX() - player->GetRectX() ,player->GetMoveY() + ydirection* player->GetRectY() ) ;
		while(!map->CanGo( gk ))
		{
			if(player->GetVecY()==0){
				assert(false);
				break;
			}
			player->DecY();
			gk=map->GetKind(player->GetStopX() - player->GetRectX() ,player->GetMoveY() + ydirection* player->GetRectY() ) ;
		}
	}

	xdirection=ydirection=0;
	if(player->GetVecX()>0){
		xdirection=1;
	}else if(player->GetVecX()<0){
		xdirection=-1;
	}
	if(player->GetVecY()>0){
		ydirection=1;
	}if(player->GetVecY()<0){
		ydirection=-1;
	}
	if(xdirection!=0 && ydirection!=0){
		gk=map->GetKind(player->GetMoveX() + xdirection*player->GetRectX() ,player->GetMoveY() + ydirection* player->GetRectY() ) ;
		while(!map->CanGo( gk ))
		{
			if(player->GetVecX()==0 && player->GetVecY()==0){
				assert(false);
				break;
			}
			player->DecXY();
			gk=map->GetKind(player->GetMoveX() + xdirection*player->GetRectX() ,player->GetMoveY() + ydirection* player->GetRectY() ) ;
		}
	}
	
	//enemy - map
	//mark - player
	return 0;
}
*/