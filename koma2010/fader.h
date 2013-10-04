#pragma once

#include "base.h"
#define FadeMax 256

class Fader{
private:
	int fin;
	int cur;
	int sp;
	CDirectX *dx;
public:
	int Set(int sfin,int speed,int scur){
		fin=sfin;
		sp=speed;
		cur=scur;
		return 0;
	}

	bool CheckEnd(){
		return fin==cur;
	}

	int GetCur(){return cur;}

	int Init(CDirectX *cdx){
		dx=cdx;
		fin=cur=FadeMax;
		return 0;
	}

	int Main(){
		if(fin!=cur){
			int dif=sp*((cur-fin)/abs(cur-fin));
			if(abs(cur-fin)<abs(dif))cur=fin;
			else cur-=dif;
		}
		return 0;
	}

	int DrawSet(){
		dx->SetScreenColor(1,1,1,(double)cur/FadeMax);
		return 0;
	}

};