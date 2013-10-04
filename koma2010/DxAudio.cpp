#include	"dx8.h"

int CDirectX::LoadWav(char *str)
{
	char log[256];
	sprintf(log,"%s‚ð2DWav‚Æ‚µ‚Ä“Ç‚Ýž‚Ý‚Ü‚·",str);
	WriteLog(log);
	audio.push_back(new Audio);
	if(audio[audio.size()-1]->LoadWavFile(str,0,lpDS)==false)
	{
		sprintf(log,"%s‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½",str);
		WriteLog(log);
		return -1;
	}
	return audio.size()-1;
}

int CDirectX::LoadWavEx(char *str)
{
	char log[256];
	sprintf(log,"%s‚ð3DWav‚Æ‚µ‚Ä“Ç‚Ýž‚Ý‚Ü‚·",str);
	WriteLog(log);
	audio.push_back(new Audio);
	if(audio[audio.size()-1]->LoadWavFileEx(str,0,lpDS)==false)
	{
		sprintf(log,"%s‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½",str);
		WriteLog(log);
		return -1;
	}
	return audio.size()-1;
}

int CDirectX::PlayNewWav(unsigned int number,float x,float y,int volume,Music_State state)
{
	if(number==-1 || number>=audio.size())
	{
		return -1;
	}
	Audio* a = new Audio;
	if(	a->PlayDuplicateWavFile(lpDS,audio[number])==true){
		audio_dup.push_back(a);
	}else{
		delete a;
		return -1;
	}
	return number;
}

void CDirectX::PlayWav(unsigned int number,float x,float y,int volume,Music_State state)
{
	LPDIRECTSOUNDBUFFER lpDSB;
	LPDIRECTSOUND3DBUFFER lp3D;
	if(number==-1 || number>=audio.size())
	{
		return;
	}
	lpDSB=audio[number]->GetWavBuffer();
	lp3D=audio[number]->GetWav3DBuffer();

		// ‰¹—Ê‚ÌÄÝ’è
	lpDSB->SetVolume(volume);

	if(audio[number]->ex==true)
	{
		lp3D->SetPosition(x,0.0f,y,DS3D_IMMEDIATE);
	}

	switch(state)
	{
	case Play:
		lpDSB->Play(0,0,0);
		break;
	case Play_Loop:
		lpDSB->Play(0,0,DSBPLAY_LOOPING);
		break;
	case Stop:
		lpDSB->Stop();
		break;
	case Rewind:
		lpDSB->SetCurrentPosition(0);
		break;
	case Replay:
		lpDSB->SetCurrentPosition(0);
		lpDSB->Play(0,0,0);
		break;
	default:
		break;
	}
}

int CDirectX::DeleteDuplicatedWav(){
	int i;

	for(i=0;i<audio_dup.size();i++){
		SAFE_DELETE(audio_dup[i]);
	}
	audio_dup.clear();
	return 0;
}