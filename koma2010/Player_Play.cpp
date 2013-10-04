#include "player.h"
#include "player_data.h"
#include "physics.h"
#include "physics_player.h"
#include "box2d_data.h"

int Player::Aiming(){
	int sflag=0;
	if(IsStop()){
		if(stopcount< STOP_FRAME)stopcount++;
	}else{
		stopcount=0;
	}
	if(stopcount>=STOP_FRAME){
		if(key->GetKeyNow(VK_RIGHT)){
			if(px<0.95)
				px+=0.1f;
		}
		if(key->GetKeyNow(VK_LEFT)){
			if(px>0.25f)
				px-=0.1f;
		}
		if(key->GetKeyNow(VK_UP)){
			if(py>-0.95)
				py-=0.1f;
		}
		if(key->GetKeyNow(VK_DOWN)){
			if(py<0.95)
				py+=0.1f;
		}
		ar = (atan2((double)mouse->GetPoint().y-240,(double)mouse->GetPoint().x-260)*360/(2*PI));
		if(ar<0)ar+=360;
		if(ar>360)ar-=360;
		if(key->GetKey(VK_RETURN) || mouse->GetLeftNow()){
			Shot();
//			px=py=0;
//			px=0.8f;
			sflag=1;
		}
	}
	return sflag;
}
int Player::Shot(){
	b2Vec2 v,p;
//	v.x=10.0f*cos(ar/360*2*PI);
//	v.y=10.0f*sin(ar/360*2*PI);
//	myBody->SetLinearVelocity(v);
	v.x=6.0f*px*cos(ar/360*2*PI);
	v.y=6.0f*px*sin(ar/360*2*PI);
	p.x=myBody->GetPosition().x;
	p.y=myBody->GetPosition().y+PLAYER_SIZE_Y/2*py;
	myBody->SetLinearVelocity(v);
	myBody->ApplyForce(v,p);
	dx->PlayNewWav(wav_shot,0,0,0,Play);
	return 0;
}

bool Player::IsStop(){
	b2Vec2 v;
	v=myBody->GetLinearVelocity();
	bool ch=(hypot(v.x,v.y)<PLAYER_EPS);
	v.x=v.y=0;
	if(ch)myBody->SetLinearVelocity(v);
	return ch;
}

bool Player::IsAiming(){
	bool b= ((stopcount>=STOP_FRAME) && IsStop());
	return b;
}

int Player::Traceup(){
	for(int i=0;i+1<TRACE;i++){
		trace[i+1]=trace[i];
	}
	trace[0]=myBody->GetPosition();
	return 0;
}