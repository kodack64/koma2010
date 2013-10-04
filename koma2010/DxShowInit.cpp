#include	"dx8.h"

Show::Show():
loop(false),
lpGraph(NULL),
lpMediaControl(NULL),
lpEvent(NULL),
lpSeek(NULL),
speed(0)
{
}

Show::~Show()
{
	lpEvent->SetNotifyWindow(NULL,0,0);
	lpGraph->Release();
	lpMediaControl->Release();
	lpEvent->Release();
	lpSeek->Release();
}

int CDirectX::DirectShowInit(HWND hwnd)
{
	show.resize(0);
	return 0;
}
