/*#include "tap.h"

int Tap::MovieNextFrame(int f){
	int atf = frame+f;
	if(atf>=MAXFRAME){
		atf=MAXFRAME-1;
	}

	int cf;
	for(cf=frame;cf<atf;cf++){
		if(rb[frame]==true){
			Next(cf);
		}else{
			Calc();
			Judge();
			Move(cf);
			rb[cf]=true;
		}
	}

	frame=atf;
	
	return 0;
}

int Tap::MovieLastFrame(int f){
	int atf = frame-f;
	if(atf<0)atf=0;

	int cf;
	for(cf=frame-1;cf>=atf;cf--){
		Back(cf);
	}
	frame=atf;
	return 0;
}
*/