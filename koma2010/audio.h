#ifndef	AUDIO_H
#define	AUDIO_H

#include	"function.h"

class Audio
{
private:
	LPDIRECTSOUNDBUFFER lpDSB;
	LPDIRECTSOUND3DBUFFER lp3D;
	LPDIRECTSOUNDBUFFER WaveLoader(char *name,LPDIRECTSOUND8 lpDS);
	LPDIRECTSOUNDBUFFER WaveLoaderEx(char *name,LPDIRECTSOUND8 lpDS);
	float	x,y;
public:
	Audio();
	virtual ~Audio();
	virtual bool LoadWavFile(char*,unsigned int number,LPDIRECTSOUND8 lpDS);
	virtual bool LoadWavFileEx(char*,unsigned int number,LPDIRECTSOUND8 lpDS);
	virtual void SetWav(LPDIRECTSOUNDBUFFER lpDSB);
	virtual bool PlayDuplicateWavFile(LPDIRECTSOUND lpDS,Audio*);
	virtual LPDIRECTSOUNDBUFFER GetWavBuffer();
	virtual LPDIRECTSOUND3DBUFFER GetWav3DBuffer();
	bool ex;
};

// グローバル変数
extern WAVEFORMATEX* m_pwfx;
extern HMMIO m_hmmioIn;
extern MMCKINFO m_ckIn;
extern MMCKINFO m_ckInRiff;

// 関数プロトタイプ
int YWaveClose();
int YWaveRead(UINT size,char *data,UINT *read,WAVEFORMATEX *wf);
int YWaveOpen(char *name);
HRESULT YWaveReadFile(HMMIO hmmioIn,UINT cbRead,BYTE* pbDest,MMCKINFO* pckIn, UINT* cbActualRead);
HRESULT YWaveStartDataRead(HMMIO* phmmioIn,MMCKINFO* pckIn,MMCKINFO* pckInRIFF);
HRESULT YWaveOpenFile(CHAR* strFileName,HMMIO* phmmioIn,WAVEFORMATEX** ppwfxInfo,MMCKINFO* pckInRIFF);
HRESULT YReadMMIO(HMMIO hmmioIn,MMCKINFO* pckInRIFF,WAVEFORMATEX **ppwfxInfo);


#endif	AUDIO_H