#include "tap.h"

int Tap::ProcLoad(){
	int a = dx->world->GetBodyCount();
	b2Body* d;
	for(b2Body* c = dx->world->GetBodyList();c;){
		d=c->GetNext();
		dx->world->DestroyBody(c);
		c=d;
	}

	stage->Reset();
	stage->Load(stagecount);

	map->Set(stage->block);
	player->Set(stage->player.x,stage->player.y,stage->player.k);
	goal->Set(stage->goal.x,stage->goal.y,stage->goal.k);
	statbar->Set(stagecount,&coin,&score,&rest,&shot);
	splash->Set(0,&stagecount,&coin,&score,&shot,&rest,&totalscore,false);
	((b2MyListener*)listen)->Set(player->GetBody(),goal->GetBody(),&coin);

	ts=ST_TAP_PLAY;
	ps=PS_MOVIE;
	ms=MS_PLAY;
	frame=0;
	fd.Set(256,8,0);
	phase=0;
	coin=0;
	score=0;
	shot=0;
	rest=stage->rest;
	return 0;
}

int Tap::Reset(){
	ts=ST_TAP_LOAD;
	stagecount=1;
	fd.Set(0,1,0);
	statbar->Reset();
	totalscore=0;
	score=0;
	regist=false;
	return 0;
}
