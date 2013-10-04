#include "tap.h"
#include "score_data.h"

int Tap::ProcPlay(){
	if(phase==0){
		if(splash->Proc()==1){
			phase=1;
		}
	}else if(phase==1){
		score= coin*100; 
		dx->world->Step(1/60.0f,6,2);
		//aiming
		player->Traceup();
		if(player->Aiming()==1){
			shot++;
		}
		if(((b2State*)(player->GetBody()->GetUserData()))->gflag>0){
			player->GoalInside();
		}else{
			player->GoalOutside();
		}
		if(player->GoalCheck() || (rest==shot && player->IsStop())){
			if(player->GoalCheck()){
				score+=SCORE_CLEAR;
				score+=coin*SCORE_CLEARCOIN;
				score+=(rest-shot)*SCORE_SHOT;
			}else{
				score = coin*SCORE_COIN;
			}
			totalscore+=score;
			splash->Set(1,&stagecount,&coin,&score,&shot,&rest,&totalscore,player->GoalCheck());
			phase=2;
		}
	}else if(phase==2){
		if(splash->Proc()==1){
			ts=ST_TAP_RESULT;
		}
	}
	return 0;
}