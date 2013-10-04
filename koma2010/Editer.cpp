#include "editer.h"

Editer::Editer(){
}

Editer::~Editer(){
}

int Editer::Main(){
	return 0;
}

int Editer::Draw(){
	return 0;
}

int Editer::Init(CDirectX *cdx,Mouse* m,Key* k){
	dx=cdx;
	mouse=m;
	key=k;
	Load();
	return 0;
}

int Editer::Load(){
	return 0;
}

int Editer::MakeCommandLine(){
	cur=0;
	return 0;
}

Command Editer::GetNextCom(){
	Command rtn=com[cur];
	cur++;
	return rtn;
}