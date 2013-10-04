#include "statbar.h"
#include "statbar_data.h"
#include "font_data.h"

Statbar::Statbar(){
}

Statbar::~Statbar(){
}

int Statbar::Proc(){
	return 0;
}

int Statbar::DrawNum(int a,int x,int y,float f){
	if(f>0.6f){
		dx->DrawGraph(x,y,NUM_WID,NUM_HEI,NUM_START_X+NUM_WID*a,NUM_START_Y,NUM_WID,NUM_HEI,0,f,img_font);
	}else{
		dx->DrawGraph(x,y,NUM_WID/2,NUM_HEI/2,NUM_START_X/2+NUM_WID/2*a,NUM_START_Y/2,NUM_WID/2,NUM_HEI/2,0,f*2,img_fonts);
	}
	return NUM_WID*f;
}

int Statbar::DrawSmallChar(int a,int x,int y,float f){
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

int Statbar::DrawLargeChar(int a,int x,int y,float f){
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

int Statbar::DrawFontString(char* s,int x,int y,float f){
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

int Statbar::Draw(){
	dx->DrawGraph(STATBAR_START_X,STATBAR_START_Y,IMG_STATBAR_WIDTH,IMG_STATBAR_HEIGHT,0,0,IMG_STATBAR_WIDTH,IMG_STATBAR_HEIGHT,img_statbar);
	char mes[256];
	sprintf(mes,"Stage %d",stage);
	DrawFontString(mes,530,10,0.3f);
	sprintf(mes,"Score");
	DrawFontString(mes,530,100,0.3f);
	sprintf(mes,"%5d",(*score));
	DrawFontString(mes,540,140,0.3f);
	sprintf(mes,"Co in");
	DrawFontString(mes,530,200,0.3f);
	sprintf(mes,"%5d",(*coin));
	DrawFontString(mes,540,240,0.3f);
	sprintf(mes,"Shot");
	DrawFontString(mes,530,300,0.3f);
	sprintf(mes,"%5d",(*shot));
	DrawFontString(mes,540,340,0.3f);
	sprintf(mes,"Rest");
	DrawFontString(mes,530,400,0.3f);
	sprintf(mes,"%5d",(*rest)-(*shot));
	DrawFontString(mes,540,440,0.3f);

	return 0;
}

int Statbar::Init(CDirectX* cdx){
	dx= cdx;
	dx->SetColorKey(false,0,0,0);
	img_statbar = dx->LoadGraph("img/statbar.bmp");
	dx->SetColorKey(true,255,255,255);
	img_font = dx->LoadGraph("img/font.bmp");
	img_fonts = dx->LoadGraph("img/font2.bmp");

	return 0;
}


int Statbar::Set(int st,int* c,int* s,int* r,int* sh){
	stage=st;
	score=s;
	coin=c;
	rest=r;
	shot=sh;
	return 0;
}

int Statbar::Reset(){
	return 0;
}