#include	"dx8.h"

void CDirectX::SetBeginTime()
{
	BeginTime=timeGetTime();
}

float CDirectX::GetGameTime()
{
	float GameTime=0;
	int subtime;
	subtime=timeGetTime()-BeginTime;
	(GameTime=subtime)/=1000;
	return GameTime;
}
