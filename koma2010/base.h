#ifndef	BASE_H
#define	BASE_H

#include	"dx8.h"

class	Base
{
private:
public:
	virtual int Main()=0;
	virtual int Draw()=0;
	virtual int Init(CDirectX	*p_dx)=0;
};

#endif	BASE_H