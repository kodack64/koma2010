#ifndef	KEY_H
#define	KEY_H

#include	"function.h"

class	Key
{
private:
	BYTE key[256];
	BYTE keyold[256];
	bool flag;
public:
	void Init()
	{
		for(int loop=0;loop<256;loop++)
		{
			key[loop]=NULL;
			keyold[loop]=NULL;
			GetKeyboardState(key);
		}
	}
	void SetKeyState()
	{
		for(int loop=0;loop<256;loop++)
		{
			keyold[loop]=key[loop];
		}
		GetKeyboardState(key);
	}
	bool GetKey(int code)
	{
		if(key[code] & 0x80)
		{
			return true;
		}
		return false;
	}
	bool GetKeyNow(int code)
	{
		if(key[code] & 0x80)
		{
			if(keyold[code] & 0x80)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		return false;
	}
	bool GetKeyOut(int code)
	{
		if(key[code] & 0x80)
		{
			return false;
		}
		else
		{
			if(keyold[code] & 0x80)
			{
				return true;
			}
		}
		return false;
	}
/*	bool GetKeyAll()
	{
		flag=false;
		for(int loop=0;loop<256;loop++)
		{
			if(key[loop] & 0x80)
			{
				flag=true;
			}
		}
		return flag;
	}*/
	int SetAllKey(char* Mes,int start)
	{
		int loop;
		for(loop=0;loop<256;loop++)
		{
			key[loop]=NULL;
			GetKeyboardState(key);
		}
		return loop;
	}
};

#endif	KEY_H