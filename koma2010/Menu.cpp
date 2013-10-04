#include "menu.h"
#include "menu_data.h"

Menu::Menu(){};

Menu::~Menu(){
}

int Menu::Main(){
	fd.Main();
	POINT at=mouse->GetPoint();
	if(fd.CheckEnd()){
		if(mouse->GetLeftNow() && dec==-1){
			if(MENU_START_X < at.x && at.x < MENU_START_X + MENU_WID){
				int mnum= (at.y - MENU_START_Y) / MENU_HEI;
				if(0<=mnum && mnum<MENU_NUM){
					dec=mnum;
					fd.Set(0,8,256);
				}
			}
		}
		else if(dec!=-1){
			return dec+1;
		}
	}
	return 0;
}

int Menu::Init(CDirectX *cdx,Mouse* m,Key* k){
	dx=cdx;
	mouse=m;
	key=k;
	fd.Init(cdx);
	Load();

	return 0;
}

int Menu::Reset(){
	fd.Set(256,8,0);
	dec=-1;
	return 0;
}

int Menu::Load(){
	dx->SetColorKey(true,0,255,0);
	img_menu=dx->LoadGraph("img/menu2.bmp");
	img_block=dx->LoadGraph("img/block2.bmp");
	return 0;
}

int Menu::Draw(){

	fd.DrawSet();

	dx->SetGraphColor(img_menu,1,1,1,1);
	dx->SetGraphColor(img_block,1,1,1,1);
	dx->DrawGraph(0,0,640,480,0,0,640,480,img_block);
	dx->DrawGraph(0,0,640,480,0,0,640,480,img_menu);

	int c;
	for(c=0;c<MENU_NUM;c++){
		POINT at = mouse->GetPoint();
		if(MENU_START_X < at.x && at.x< MENU_START_X + MENU_WID && 
			MENU_START_Y+MENU_HEI*c < at.y && at.y <  MENU_START_Y + MENU_HEI*(c+1)){
			dx->SetGraphColor(img_menu,1,1,1,1);
		}
		else{
			dx->SetGraphColor(img_menu,1,1,1,0.6f);
		}
		dx->DrawGraph(MENU_START_X,MENU_START_Y+MENU_HEI*c,MENU_WID,MENU_HEI,
			IMG_MENU_START_X,IMG_MENU_START_Y+MENU_HEI*c,MENU_WID,MENU_HEI,img_menu);
	}
	return 0;
}