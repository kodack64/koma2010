#include "splash.h"
#include "font_data.h"
#include "splash_data.h"
#include "score_data.h"

Splash::Splash(){
}

Splash::~Splash(){
}

int Splash::DrawNum(int a,int x,int y,float f){
	if(f>0.6f){
		dx->DrawGraph(x,y,NUM_WID,NUM_HEI,NUM_START_X+NUM_WID*a,NUM_START_Y,NUM_WID,NUM_HEI,0,f,img_font);
	}else{
		dx->DrawGraph(x,y,NUM_WID/2,NUM_HEI/2,NUM_START_X/2+NUM_WID/2*a,NUM_START_Y/2,NUM_WID/2,NUM_HEI/2,0,f*2,img_fonts);
	}
	return NUM_WID*f;
}

int Splash::DrawSmallChar(int a,int x,int y,float f){
	int b=a/CHAR_RETURN_NUM;
	a%=CHAR_RETURN_NUM;
	if(f>0.6f){
		dx->DrawGraph(x , y , CHAR_WID[b][a+1]-CHAR_WID[b][a] , CHAR_HEI ,
			CHAR_WID[b][a],CHAR_START_Y+CHAR_HEI*b , CHAR_WID[b][a+1]-CHAR_WID[b][a] , CHAR_HEI , 0 , f ,img_font);
	}else{
		dx->DrawGraph(x , y , (CHAR_WID[b][a+1]-CHAR_WID[b][a])/2 , CHAR_HEI/2 ,
			CHAR_WID[b][a]/2,(CHAR_START_Y+CHAR_HEI*b)/2 , (CHAR_WID[b][a+1]-CHAR_WID[b][a])/2 , (CHAR_HEI)/2 , 0 , f*2 ,img_fonts);
	}
	return (CHAR_WID[b][a+1]-CHAR_WID[b][a])*f;
}

int Splash::DrawLargeChar(int a,int x,int y,float f){
	int b=a/CHAR_RETURN_NUM+2;
	a%=CHAR_RETURN_NUM;
	if(f>0.6f){
		dx->DrawGraph(x , y , CHAR_WID[b][a+1]-CHAR_WID[b][a] , CHAR_HEI ,
			CHAR_WID[b][a],CHAR_START_Y+CHAR_HEI*b , CHAR_WID[b][a+1]-CHAR_WID[b][a] , CHAR_HEI , 0 , f ,img_font);
	}else{
		dx->DrawGraph(x , y , (CHAR_WID[b][a+1]-CHAR_WID[b][a])/2 , CHAR_HEI/2 ,
			CHAR_WID[b][a]/2,(CHAR_START_Y+CHAR_HEI*b)/2 , (CHAR_WID[b][a+1]-CHAR_WID[b][a])/2 , (CHAR_HEI)/2 , 0 , f*2 ,img_fonts);
	}
	return (CHAR_WID[b][a+1]-CHAR_WID[b][a])*f;
}

int Splash::DrawFontString(char* s,int x,int y,float f){
	int c;
	for(c=0;c<strlen(s);c++){
		if('0'<=s[c] && s[c]<='9'){
			x+=DrawNum(s[c]-'0',x,y,f);
		}else if('a'<=s[c] && s[c]<='z'){
			x+=DrawSmallChar(s[c]-'a',x,y,f);
		}else if('A'<=s[c] && s[c]<='Z'){
			x+=DrawLargeChar(s[c]-'A',x,y,f);
		}else{
			x+=NUM_WID*0.8f*f;
		}
	}
	return 0;
}

int Splash::Draw(){
	double c;
	char mes[256];
	int cdf=100;
	int cdh=200;
	int cdf2=50;
	int cdff=60;
	if(type==0){
		sprintf(mes,"Stage %d",*stage);
		if(time<MAX_SPLASH/2){
			dx->SetGraphColor(img_font,1,1,1,1);
			dx->SetGraphColor(img_fonts,1,1,1,1);
			dx->SetGraphColor(img_splash,1,1,1,1);
			c = sin(((double)time/(MAX_SPLASH/2)) *PI/2);
		}else{
			float b;
			int tt=time;
			b=1.0f-1.0f*((double)(tt-MAX_SPLASH/2)/(MAX_SPLASH/2));
			dx->SetGraphColor(img_font,b,b,b,b);
			dx->SetGraphColor(img_fonts,b,b,b,b);
			dx->SetGraphColor(img_splash,b,b,b,b);
			c=1;
		}
		dx->DrawGraph(128,-64+240*c,256,128,0,0,256,128,img_splash);
		DrawFontString(mes,128+50,-64+240*c+40,0.4f);
	}else if(type==1){
		if(time<MAX_SPLASH/2){
			dx->SetGraphColor(img_font,1,1,1,1);
			dx->SetGraphColor(img_fonts,1,1,1,1);
			dx->SetGraphColor(img_splash2,1,1,1,1);
			c = sin(((double)time/(MAX_SPLASH/2)) *PI/2);
		}else{
			float b;
			int tt=time;
			b=1.0f-1.0f*((double)(tt-MAX_SPLASH/2)/(MAX_SPLASH/2));
			b;
			dx->SetGraphColor(img_font,b,b,b,b);
			dx->SetGraphColor(img_fonts,b,b,b,b);
			dx->SetGraphColor(img_splash2,b,b,b,b);
			c=1;
		}
		dx->DrawGraph(50,-640+(680)*c,512,512,0,0,512,512,img_splash2);
		sprintf(mes,"Result");
		DrawFontString(mes,cdf+60		,-640+(680)*c+cdff-40,0.7f);
		sprintf(mes,"Stage %d",*stage);
		DrawFontString(mes,cdf+100	,-640+(680)*c+cdff+cdf2*1-20,0.3f);
		sprintf(mes,"Clear");
		DrawFontString(mes,cdf		,-640+(680)*c+cdff+cdf2*2,0.5f);
		if(clear){
			sprintf(mes,"%5d",SCORE_CLEAR);
		}else{
			sprintf(mes,"%5d",0);
		}
		DrawFontString(mes,cdf+cdh	,-640+(680)*c+cdff+cdf2*2,0.5f);
		sprintf(mes,"Shot");
		DrawFontString(mes,cdf		,-640+(680)*c+cdff+cdf2*3,0.5f);
		sprintf(mes,"%5d",((*rest)-(*shot))*SCORE_SHOT);
		DrawFontString(mes,cdf+cdh	,-640+(680)*c+cdff+cdf2*3,0.5f);
		sprintf(mes,"Co in");
		DrawFontString(mes,cdf		,-640+(680)*c+cdff+cdf2*4,0.5f);
		if(clear){
			sprintf(mes,"%5d",(*coin)*SCORE_CLEARCOIN);
		}else{
			sprintf(mes,"%5d",(*coin)*SCORE_COIN);
		}
		DrawFontString(mes,cdf+cdh	,-640+(680)*c+cdff+cdf2*4,0.5f);
		sprintf(mes,"Score");
		DrawFontString(mes,cdf		,-640+(680)*c+cdff+cdf2*5,0.5f);
		sprintf(mes,"%5d",*score);
		DrawFontString(mes,cdf+cdh	,-640+(680)*c+cdff+cdf2*5,0.5f);
	}else{
		if(time<MAX_SPLASH/2){
			dx->SetGraphColor(img_font,1,1,1,1);
			dx->SetGraphColor(img_fonts,1,1,1,1);
			dx->SetGraphColor(img_splash3,1,1,1,1);
			c = sin(((double)time/(MAX_SPLASH/2)) *PI/2);
		}else{
			float b;
			int tt=time;
			b=1.0f-1.0f*((double)(tt-MAX_SPLASH/2)/(MAX_SPLASH/2));
			b;
			dx->SetGraphColor(img_font,b,b,b,b);
			dx->SetGraphColor(img_fonts,b,b,b,b);
			dx->SetGraphColor(img_splash3,b,b,b,b);
			c=1;
		}
		int tt=-640+(640)*c;
		dx->DrawGraph(10,tt,640,480,0,0,640,480,img_splash3);
		sprintf(mes,"Total Result");
		DrawFontString(mes,cdf+60		,tt+cdff-40,0.7f);
		sprintf(mes,"Total Score");
		DrawFontString(mes,cdf		,tt+cdff+cdf2*2,0.5f);
		sprintf(mes,"%5d",*totalscore);
		DrawFontString(mes,cdf+cdh+30	,tt+cdff+cdf2*2,0.5f);
		sprintf(mes,"Rank");
		DrawFontString(mes,cdf		,tt+cdff+cdf2*3,0.5f);
		sprintf(mes,"%4dth   %4d",*rank,*playnum);
		DrawFontString(mes,cdf+cdh	,tt+cdff+cdf2*3,0.5f);
		dx->DrawGraph(cdf+cdh+40+100,tt+cdff+cdf2*3-5,64,64,0,0,64,64,0,1.0f,img_slash);
		sprintf(mes,"Top Score");
		DrawFontString(mes,cdf		,tt+cdff+cdf2*4,0.5f);
		sprintf(mes,"%5d",*topscore);
		DrawFontString(mes,cdf+cdh+30	,tt+cdff+cdf2*4,0.5f);
		sprintf(mes,"  Thank You");
		DrawFontString(mes,cdf		,tt+cdff+cdf2*5.5,0.5f);
		sprintf(mes,"           for Playing");
		DrawFontString(mes,cdf		,tt+cdff+cdf2*6.5,0.5f);
	}
	return 0;
}

int Splash::Init(CDirectX *cdx,Mouse* mouse,Key* key){
	dx=cdx;
	m=mouse;
	k=key;
	dx->SetColorKey(true,0,255,0);
	img_splash =dx->LoadGraph("img/splash.bmp");
	img_splash2 =dx->LoadGraph("img/splash2.bmp");
	img_splash3 =dx->LoadGraph("img/splash3.bmp");
	dx->SetColorKey(true,255,255,255);
	img_font =dx->LoadGraph("img/font.bmp");
	img_fonts =dx->LoadGraph("img/font2.bmp");
	img_slash = dx->LoadGraph("img/slash.bmp");
	return 0;
}

int Splash::Set(int i,int* st,int*co,int*sc,int*sh,int*re,int*tot,bool cl){
	type=i;
	stage =st;
	coin=co;
	score=sc;
	shot=sh;
	rest=re;
	time=0;
	totalscore=tot;
	clear = cl;
	flag=true;
	return 0;
}
int Splash::Proc(){
	if(time<MAX_SPLASH/2){
		time++;
	}else if(flag){
		if(m->GetLeftNow() || k->GetKeyNow(VK_RETURN)){
			flag=false;
		}
	}else if(time<MAX_SPLASH){
		time++;
	}else{
		return 1;
	}
	return 0;
}

int Splash::Set2(int* ra,int*to,int*pl){
	rank=ra;
	topscore=to;
	playnum=pl;
	return 0;
}