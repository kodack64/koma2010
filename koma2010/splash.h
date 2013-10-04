#include "dx8.h"

class Splash{
private:
	int img_splash;
	int img_font;
	int img_fonts;
	int img_splash2;
	int img_splash3;
	int img_slash;
	CDirectX* dx;
	int type;
	int time;

	int *stage;
	int *coin;
	int *score;
	int *totalscore;
	int *shot;
	int *rest;
	int *topscore;
	int *rank;
	int *playnum;
	bool clear;

	Mouse* m;
	Key* k;
	bool flag;

public:
	Splash();
	virtual ~Splash();

	virtual int Init(CDirectX *dx,Mouse*,Key*);
	virtual int Set(int i,int*stage,int*coin,int*score,int*shot,int*rest,int*totalscore,bool clear);
	virtual int Set2(int*rank,int*topscore,int*playnum);
	virtual int Proc();
	virtual int Draw();
	virtual int DrawFontString(char*,int,int,float);
	virtual int DrawNum(int a,int x,int y,float);
	virtual int DrawSmallChar(int a,int x,int y,float);
	virtual int DrawLargeChar(int a,int x,int y,float);
};