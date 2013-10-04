#include "contact_listener.h"

void b2MyListener::BeginContact(b2Contact* contact){
	b2Body* A = contact->GetFixtureA()->GetBody(); 
	b2Body* B = contact->GetFixtureB()->GetBody();

//	char st[256];
	b2State* As;
	b2State* Bs;
	As=(b2State*)(A->GetUserData());
	Bs=(b2State*)(B->GetUserData());
//	sprintf(st,"(%d,%d) with (%d,%d)",As->kind,As->type,Bs->kind,Bs->type);
//	SetWindowText(GetWindowHandle(),st);

	//player with dynamic block
	if((As->kind==0 && Bs->kind==1) ||
		(Bs->kind==0 && As->kind==1)){
		dx->PlayNewWav(wav_crash2,0,0,-500,Play);
	}else if(As->kind==1 && Bs->kind==1){ // dynamic block with dynamic block
		int wx=A->GetPosition().x-pl->GetPosition().x;
		int wy=A->GetPosition().y-pl->GetPosition().y;
		double dist=hypot(wx,wy);
		int vol = -1000+ 500*min(1,dist/1000);
		dx->PlayNewWav(wav_crash1,wx,wy,vol,Play);
	}
	//player reachs to goal
	if((As->kind==0 && Bs->kind==2) || (Bs->kind==0 && As->kind==2)){
		((b2State*)(pl->GetUserData()))->gflag++;
	}
	//player reachs to coin
	if((As->kind==0 && Bs->kind==3 && Bs->gflag==0) || (Bs->kind==0 && As->kind==3 && As->gflag==0)){
		if(As->kind==3){
			((b2State*)(A->GetUserData()))->gflag=1;
		}else{
			((b2State*)(B->GetUserData()))->gflag=1;
		}
		(*coin)++;
		dx->PlayNewWav(wav_coin,0,0,-100,Play);
	}
}

void b2MyListener::EndContact(b2Contact* contact){
	b2Body* A = contact->GetFixtureA()->GetBody(); 
	b2Body* B = contact->GetFixtureB()->GetBody();
	b2State* As;
	b2State* Bs;
	As=(b2State*)(A->GetUserData());
	Bs=(b2State*)(B->GetUserData());
	if((As->kind==0 && Bs->kind==2) || (Bs->kind==0 && As->kind==2)){
		((b2State*)(pl->GetUserData()))->gflag--;
	}
}

int b2MyListener::Init(CDirectX* sdx){
	dx=sdx;
	wav_crash1 = dx->LoadWavEx("wav/c3mn.wav");
	wav_crash2 = dx->LoadWav("wav/c2st.wav");
	wav_coin = dx->LoadWav("wav/coin.wav");
	return 0;
}