#include	"show.h"

bool Show::LoadMp3File(const unsigned short *str)
{
//	CoInitialize(NULL);
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,IID_IGraphBuilder, (void **)&lpGraph);
	lpGraph->QueryInterface(IID_IMediaControl, (void **)&lpMediaControl);
	lpGraph->QueryInterface(IID_IMediaEventEx, (void **)&lpEvent);
	lpGraph->QueryInterface(IID_IMediaSeeking, (void**)&lpSeek);
	lpEvent->SetNotifyWindow((OAHWND)GetWindowHandle(), WM_GRAPHNOTIFY, 0);
	lpGraph->RenderFile((LPCWSTR)str, NULL);
	return true;
}


void Show::CheckMp3State()
{
	long filt=0;
	if(loop==true)
	{
		lpMediaControl->GetState(INFINITE,&filt);
		if(filt==State_Stopped)
		{
			lpMediaControl->Run();
		}
	}
}