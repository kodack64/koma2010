#ifndef	APPLI_H
#define	APPLI_H

#include	"dx8.h"
#include	"game.h"

class Appli:public Base
{
private:
	Appli(const Appli &right);
	const Appli & operator=(const Appli &right);
	Game	*game;
	int State;
public:
	Appli();
	virtual ~Appli();
	virtual int Main();
	virtual int Init(CDirectX *directx);
	virtual int Draw();
};

#endif	APPLI_H