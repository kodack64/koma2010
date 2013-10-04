#include	"dx8.h"

int CDirectX::LoadMusic(char* str)
{
	
	WCHAR tmp[MAX_PATH];
	MultiByteToWideChar(CP_ACP,0,GetMyDir(),-1,tmp,MAX_PATH);
	MultiByteToWideChar(CP_ACP,0,str,-1,tmp,MAX_PATH);

	char log[256];
	sprintf(log,"  %s‚ğMp3‚Æ‚µ‚Ä“Ç‚İ‚İ‚Ü‚·",str);
	WriteLog(log);
	show.push_back(new Show);
	if(show[show.size()-1]->LoadMp3File((const unsigned short*)tmp)==false)
	{
		sprintf(log,"  %s‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚Ü‚µ‚½",str);
		WriteLog(log);
		return -1;
	}
	return 	show.size()-1;
}

void CDirectX::PlayMusic(unsigned int number,Music_State state)
{
	if(number==-1 || number>show.size())
	{
		return;
	}

	IMediaControl *lpMediaControl=NULL;
	IMediaSeeking *lpSeek=NULL;
	
	lpMediaControl=show[number]->GetMediaControl();
	lpSeek=show[number]->GetMediaSeeking();
	LONGLONG a=0;
	lpSeek->SetRate(show[number]->GetSpeed());
	switch(state)
	{
	case Play:
		lpMediaControl->Run();
		break;
	case Play_Loop:
		lpMediaControl->Run();
		show[number]->loop=true;
		break;
	case Stop:
		lpMediaControl->Stop();
		break;
	case Rewind:
		lpMediaControl->Stop();
		lpSeek->SetPositions(&a,AM_SEEKING_AbsolutePositioning,NULL, AM_SEEKING_NoPositioning);
		lpMediaControl->Run();
		break;
	}
}

int CDirectX::SetSpeed(unsigned int number,double speed)
{
	if(number==-1 || number>show.size())
	{
		return -1;
	}
	show[number]->SetSpeed(speed);
	return 0;
}