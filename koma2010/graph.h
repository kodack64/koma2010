#ifndef	BITMAP_H
#define	BITMAP_H

#include	"function.h"

class Graph
{
private:
	LPDIRECT3DTEXTURE8 mybitmap;
	D3DSURFACE_DESC desc;
	int width;
	int height;
	float col_blue;
	float col_red;
	float col_green;
	float col_light;
	int center_x;
	int center_y;
public:
	Graph();
	virtual ~Graph();
	virtual bool LoadGraphFile(const char*,LPDIRECT3DDEVICE8 lpD3DDEV,bool,int,int,int);
	void SetColor(float red,float blue,float green,float light)
	{
		col_red=red;
		col_blue=blue;
		col_green=green;
		col_light=light;
	}
	void SetCenter(bool flag,int x,int y)
	{
		if(flag==true)
		{
			center_x=x;
			center_y=y;
		}
		else
		{
			center_x=width/2;
			center_y=height/2;
		}
	}
	float GetColorRed(){return col_red;}
	float GetColorBlue(){return col_blue;}
	float GetColorGreen(){return col_green;}
	float GetColorLight(){return col_light;}
	virtual LPDIRECT3DTEXTURE8	GetBitMap(void);
	int	GetWidth(void)
	{
		return width;
	}
	int GetHeight(void)
	{
		return height;
	}
	int GetCenterX(void)
	{
		return center_x;
	}
	int GetCenterY(void)
	{
		return center_y;
	}
};

#endif	BITMAP_H