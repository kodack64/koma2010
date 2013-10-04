#include	"audio.h"

Audio::Audio():
lpDSB(NULL),
lp3D(NULL)
{
}

Audio::~Audio()
{
	RELEASE(lpDSB);
	RELEASE(lp3D);
}

bool Audio::LoadWavFile(char *dir,unsigned int number,LPDIRECTSOUND8 lpDS)
{
	lpDSB = WaveLoader(dir,lpDS);
	if (!lpDSB)
	{
		MessageBox(NULL,"wavファイルが見つかりません","error",MB_OK);
		return false;
	}
	return true;
}	

bool Audio::LoadWavFileEx(char *dir,unsigned int number,LPDIRECTSOUND8 lpDS)
{
	lpDSB = WaveLoaderEx(dir,lpDS);
	if (!lpDSB)
	{
		MessageBox(NULL,"wavファイルが見つかりません","error",MB_OK);
		return false;
	}
	lpDSB->QueryInterface(IID_IDirectSound3DBuffer,(void **)&lp3D);
	if(ex==true)
	{
		lp3D->SetPosition(0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
		lp3D->SetVelocity(0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
		x=y=0.0f;
	}
	return true;
}

void Audio::SetWav(LPDIRECTSOUNDBUFFER slpDSB)
{
	if(lpDSB==NULL)
	{
		lpDSB=slpDSB;
	}
}

bool Audio::PlayDuplicateWavFile(LPDIRECTSOUND lpDS,Audio* a){
	if(lpDSB!=NULL)return false;
	lpDS->DuplicateSoundBuffer(a->GetWavBuffer(),&lpDSB);
	if(a->ex==true)
	{
		lpDSB->QueryInterface(IID_IDirectSound3DBuffer,(void **)&lp3D);
		lp3D->SetPosition(x,0.0f,y,DS3D_IMMEDIATE);
	}
	lpDSB->Play(0,0,0);
	return true;
}

LPDIRECTSOUNDBUFFER Audio::GetWavBuffer()
{
	return lpDSB;
}

LPDIRECTSOUND3DBUFFER Audio::GetWav3DBuffer()
{
	return lp3D;
}