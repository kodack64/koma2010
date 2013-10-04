#pragma once

#include "base.h"
#include "editer.h"
#include "command.h"

class Editer{
private:
	CDirectX *dx;
	Mouse* mouse;
	Key* key;

	vector <Command> com;
	int cur;
public:
	Editer();
	virtual ~Editer();

	virtual int Main();
	virtual int Draw();
	virtual int Init(CDirectX *dx,Mouse* m ,Key* k);
	virtual int Load();
	virtual Command GetNextCom();
	virtual int MakeCommandLine();
};