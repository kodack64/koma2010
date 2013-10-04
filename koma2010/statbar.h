#include "dx8.h"

class Statbar{
private:

	CDirectX *dx;
	int img_statbar;
	int img_font;
	int img_fonts;
	int stage;
	int* score;
	int* coin;
	int* rest;
	int* shot;
	int px;
	int py;
public:
	Statbar();
	virtual ~Statbar();
	virtual int Draw();
	virtual int Init(CDirectX* dx);
	virtual int Set(int Stage,int* coin,int* score,int*rest,int*shot);
	virtual int Proc();
	virtual int Reset();

	virtual int DrawFontString(char*,int,int,float);
	virtual int DrawNum(int a,int x,int y,float);
	virtual int DrawSmallChar(int a,int x,int y,float);
	virtual int DrawLargeChar(int a,int x,int y,float);
};