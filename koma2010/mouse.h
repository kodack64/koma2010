#ifndef	MOUSE_H
#define	MOUSE_H

#include	"function.h"

class	Mouse
{
private:
	POINT	m;
	bool	right;
	bool	rightold;
	bool	left;
	bool	leftold;
public:
	void Init()
	{
		m.x=0;
		m.y=0;
		right=false;
		rightold=false;
		left=false;
		leftold=false;
	}
	void SetMouse()
	{
		GetCursorPos(&m);
		ScreenToClient(GetWindowHandle(),&m);

		leftold=left;
		rightold=right;

		if(GetKeyState(1) & 0x80)
		{
			left=true;
		}
		else
		{
			left=false;
		}
		if(GetKeyState(2) & 0x80)
		{
			right=true;
		}
		else
		{
			right=false;
		}
	}
	void SetMouseCursor(POINT m){
		ClientToScreen(GetWindowHandle(),&m);
		SetCursorPos(m.x,m.y);
	}

	POINT GetPoint(){return m;}
	bool GetLeft(){return left;}
	bool GetRight(){return right;}
	bool GetLeftNow()
	{
		if(left==true && leftold==false)	return true;
		else								return false;
	}
	bool GetRightNow()
	{
		if(right==true && rightold==false)	return true;
		else								return false;
	}
	bool GetLeftOut()
	{
		if(left==false && leftold==true)	return true;
		else								return false;
	}
	bool GetRightOut()
	{
		if(right==false && rightold==true)	return true;
		else								return false;
	}
	void SetAll(int sright,int sleft,int sx,int sy)
	{
		if(sright==0)	right=false;
		else			right=true;
		if(sleft==0)	left=false;
		else			left=true;
		m.x=sx;
		m.y=sy;
	}
};

#endif	MOUSE_H
