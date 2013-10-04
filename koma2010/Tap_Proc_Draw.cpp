#include "tap.h"
#include "box2d_data.h"
#include "var.h"

int Tap::ProcDraw(){
	if(mouse->GetRightNow()){
		mp=mouse->GetPoint();
	}
	if(mouse->GetRight()){
		dx->SetSlideDrawScreenCenter((int)(260-player->GetX()*MtoPIX*perc)+mouse->GetPoint().x-mp.x,(int)(240-player->GetY()*MtoPIX*perc)+mouse->GetPoint().y-mp.y);
	}else{
		dx->SetSlideDrawScreenCenter((int)(260-player->GetX()*MtoPIX*perc),(int)(240-player->GetY()*MtoPIX*perc));
	}
	map->Draw();
	goal->Draw();
	player->Draw();
	dx->SetSlideDrawScreenCenter(0,0);
	statbar->Draw();
	if(phase!=1){
		splash->Draw();
	}
	return 0;
}

int Tap::ProcResultDraw(){
	map->DrawTile();
	splash->Draw();
	return 0;
}