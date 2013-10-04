#include "tap.h"
#include "box2d_data.h"
#include "map_data.h"

Tap::Tap()
{
}

Tap::~Tap(){
	delete stage;
	delete map;
	delete goal;
	delete player;
	delete statbar;
	delete splash;
	delete listen;
	delete (dx->world);
}

int Tap::Init(CDirectX *cdx , Mouse *m , Key *k){
	dx=cdx;
	mouse=m;
	key=k;

	stage = new Stage;
	map = new Map;
	map->Init(dx,mouse,key);
	player = new Player;
	player->Init(dx,mouse,key);
	goal = new Goal;
	goal->Init(dx);
	statbar = new Statbar;
	statbar->Init(dx);
	splash = new Splash;
	splash->Init(dx,mouse,key);
	listen = new b2MyListener;
	((b2MyListener*)listen)->Init(dx);
	fd.Init(dx);

	b2Vec2 gravity(0.0f,GRAVITY);
	dx->world = new b2World(gravity,true);
	dx->world->SetContactListener(listen);

	FILE* fp;
	fp=fopen("stage/num.txt","r");
	if(fp!=NULL){
		fscanf(fp,"%d",&MaxStage);
		fclose(fp);
	}else{
		WriteLog("マップ数定義ファイルが見つかりません");
		MaxStage=0;
	}
	return 0;
}

int Tap::Main(){
	fd.Main();
	switch(ts){
	case ST_TAP_LOAD:
		ProcLoad();
		break;

	case ST_TAP_PLAY:
		ProcPlay();
		break;

	case ST_TAP_RESULT:
		if(ProcResult()==1){
			return 1;
		}
		break;
	}

	return 0;
}

int Tap::Draw(){
	fd.DrawSet();
	switch(ts){
	case ST_TAP_LOAD:
		break;
	case ST_TAP_PLAY:
		ProcDraw();
		break;
	case ST_TAP_RESULT:
		ProcResultDraw();
		break;
	}
	return 0;
}



