#include	"audio.h"

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <dsound.h>

// �O���[�o���ϐ�
WAVEFORMATEX* m_pwfx;
HMMIO m_hmmioIn;
MMCKINFO m_ckIn;
MMCKINFO m_ckInRiff;

LPDIRECTSOUNDBUFFER Audio::WaveLoaderEx(char *name,LPDIRECTSOUND8 lpDS)
{
	char *buf;
	UINT readsize;
	WAVEFORMATEX wf;
	LPDIRECTSOUNDBUFFER lpDSB = NULL;
	DSBUFFERDESC desc;
	LPVOID pMem1,pMem2;
	DWORD size1,size2;
	// WAVE �t�@�C�����J��
	if (!YWaveOpen(name))
	{
		return NULL;
	}
	// �������̈�̊m��
	buf = (char *)malloc(m_ckIn.cksize);
	// �ǂݍ���
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	if (!YWaveRead(m_ckIn.cksize,buf,&readsize,&wf))
	{
		free(buf);
		return NULL;
	}
	// �T�E���h�o�b�t�@�̍쐬
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	desc.dwBufferBytes = readsize;
	desc.lpwfxFormat = &wf;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSB,NULL)))
	{
		free(buf);
		return NULL;
	}
	// �̈�����b�N
	if (FAILED(lpDSB->Lock(0,readsize,&pMem1,&size1,&pMem2,&size2,0)))
	{
		free(buf);
		return 0;
	}
	// ��������
	memcpy(pMem1,buf,size1);
	if (size2)
	{
		memcpy(pMem2,buf + size1,size2);
	}
	// ���b�N����
	lpDSB->Unlock(pMem1,size1,pMem2,size2);
	free(buf);
	// ����
	YWaveClose();
	ex=true;
	return lpDSB;
}

LPDIRECTSOUNDBUFFER Audio::WaveLoader(char *name,LPDIRECTSOUND8 lpDS)
{
	char *buf;
	UINT readsize;
	WAVEFORMATEX wf;
	LPDIRECTSOUNDBUFFER lpDSB = NULL;
	DSBUFFERDESC desc;
	LPVOID pMem1,pMem2;
	DWORD size1,size2;
	// WAVE �t�@�C�����J��
	if (!YWaveOpen(name))
	{
		return NULL;
	}
	// �������̈�̊m��
	buf = (char *)malloc(m_ckIn.cksize);
	// �ǂݍ���
	ZeroMemory(&wf,sizeof(WAVEFORMATEX));
	if (!YWaveRead(m_ckIn.cksize,buf,&readsize,&wf))
	{
		free(buf);
		return NULL;
	}
	// �T�E���h�o�b�t�@�̍쐬
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_GLOBALFOCUS | DSBCAPS_LOCDEFER | DSBCAPS_CTRLVOLUME;
	desc.dwBufferBytes = readsize;
	desc.lpwfxFormat = &wf;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSB,NULL)))
	{
		free(buf);
		return NULL;
	}
	// �̈�����b�N
	if (FAILED(lpDSB->Lock(0,readsize,&pMem1,&size1,&pMem2,&size2,0)))
	{
		free(buf);
		return 0;
	}
	// ��������
	memcpy(pMem1,buf,size1);
	if (size2)
	{
		memcpy(pMem2,buf + size1,size2);
	}
	// ���b�N����
	lpDSB->Unlock(pMem1,size1,pMem2,size2);
	free(buf);
	// ����
	YWaveClose();
	ex=false;
	return lpDSB;
}


/* WAVE ���� */
int YWaveClose()
{
	mmioClose(m_hmmioIn,0);
	return 1;
}

/* WAVE �ǂݍ��� */
int YWaveRead(UINT size,char *data,UINT *read,WAVEFORMATEX *wf)
{
	if (FAILED(YWaveReadFile(m_hmmioIn,size,(BYTE *)data,&m_ckIn,read)))
	{
		return 0;
	}
	/* �t�H�[�}�b�g�̃R�s�[ */
	if (wf)
	{
		memcpy(wf,m_pwfx,sizeof(WAVEFORMATEX));
	}
	free(m_pwfx);
	return 1;
}

/* WAVE �J�� */
int YWaveOpen(char *name)
{
	m_pwfx = NULL;
	if (FAILED(YWaveOpenFile(name,&m_hmmioIn,&m_pwfx,&m_ckInRiff)))
	{
		return 0;
	}
	if (FAILED(YWaveStartDataRead(&m_hmmioIn,&m_ckIn,&m_ckInRiff)))
	{
		return 0;
	}
	return 1;
}

/* WAVE �t�@�C���ǂݍ��� */
HRESULT YWaveReadFile(HMMIO hmmioIn,UINT cbRead,BYTE* pbDest,MMCKINFO* pckIn, UINT* cbActualRead)
{
	MMIOINFO mmioinfoIn;
	*cbActualRead = 0;
	if (mmioGetInfo(hmmioIn,&mmioinfoIn,0))
	{
		return E_FAIL;
	}
	UINT cbDataIn;
	cbDataIn = cbRead;
	if (cbDataIn > pckIn->cksize) 
	{
		cbDataIn = pckIn->cksize;
	}
	pckIn->cksize -= cbDataIn;
	for (DWORD cT = 0;cT < cbDataIn;cT++)
	{
		if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
		{
			if (mmioAdvance(hmmioIn,&mmioinfoIn,MMIO_READ))
			{
				return E_FAIL;
			}
			if (mmioinfoIn.pchNext == mmioinfoIn.pchEndRead)
			{
				return E_FAIL;
			}
		}
		*((BYTE *)pbDest + cT) = *((BYTE *)mmioinfoIn.pchNext);
		mmioinfoIn.pchNext++;
	}
	if (mmioSetInfo(hmmioIn,&mmioinfoIn,0))
	{
		return E_FAIL;
	}
	*cbActualRead = cbDataIn;
	return S_OK;
}

/* WAVE �f�[�^�ǂݍ��� */
HRESULT YWaveStartDataRead(HMMIO* phmmioIn,MMCKINFO* pckIn,MMCKINFO* pckInRIFF)
{
	if (-1 == mmioSeek(*phmmioIn,pckInRIFF->dwDataOffset + sizeof(FOURCC),SEEK_SET))
	{
		return E_FAIL;
	}
	pckIn->ckid = mmioFOURCC('d','a','t','a');
	if (mmioDescend(*phmmioIn,pckIn,pckInRIFF,MMIO_FINDCHUNK))
	{
		return E_FAIL;
	}
	return S_OK;
}

/* Wave ���J�� */
HRESULT YWaveOpenFile(CHAR* strFileName,HMMIO* phmmioIn,WAVEFORMATEX** ppwfxInfo,MMCKINFO* pckInRIFF)
{
	HRESULT hr;
	HMMIO hmmioIn;
	hmmioIn = NULL;
	if (!(hmmioIn = mmioOpen(strFileName,NULL,MMIO_ALLOCBUF | MMIO_READ)))
	{
		return E_FAIL;
	}
	if (FAILED(hr = YReadMMIO(hmmioIn,pckInRIFF,ppwfxInfo)))
	{
		mmioClose(hmmioIn,0);
		return E_FAIL;
	}
	*phmmioIn = hmmioIn;
	return S_OK;
}

/* MMIO �ǂݍ��� */
HRESULT YReadMMIO(HMMIO hmmioIn,MMCKINFO* pckInRIFF,WAVEFORMATEX **ppwfxInfo)
{
	MMCKINFO ckIn;
	PCMWAVEFORMAT pcmWaveFormat;
	*ppwfxInfo = NULL;
	if (mmioDescend(hmmioIn,pckInRIFF,NULL,0))
	{
		return E_FAIL;
	}
	if ((pckInRIFF->ckid != FOURCC_RIFF) || (pckInRIFF->fccType != mmioFOURCC('W','A','V','E')))
	{
		return E_FAIL;
	}
	ckIn.ckid = mmioFOURCC('f','m','t',' ');
	if (mmioDescend(hmmioIn,&ckIn,pckInRIFF,MMIO_FINDCHUNK))
	{
		return E_FAIL;
	}
	if (ckIn.cksize < (LONG)sizeof(PCMWAVEFORMAT))
	{
		return E_FAIL;
	}
	if (mmioRead(hmmioIn,(HPSTR)&pcmWaveFormat,sizeof(pcmWaveFormat)) != sizeof(pcmWaveFormat))
	{
		return E_FAIL;
	}
	if (pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM)
	{
		if (!(*ppwfxInfo = (WAVEFORMATEX *)malloc(sizeof(WAVEFORMATEX))))
		{
			return E_FAIL;
		}
		memcpy(*ppwfxInfo,&pcmWaveFormat,sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = 0;
	}
	else
	{
		WORD cbExtraBytes;
		cbExtraBytes = 0;
		if (mmioRead(hmmioIn,(CHAR *)&cbExtraBytes,sizeof(WORD)) != sizeof(WORD))
		{
			return E_FAIL;
		}
		*ppwfxInfo = (WAVEFORMATEX *)new CHAR[sizeof(WAVEFORMATEX) + cbExtraBytes];
		if (!*ppwfxInfo)
		{
			return E_FAIL;
		}
		memcpy(*ppwfxInfo,&pcmWaveFormat,sizeof(pcmWaveFormat));
		(*ppwfxInfo)->cbSize = cbExtraBytes;
		if (mmioRead(hmmioIn,(CHAR *)(((BYTE *) & ((*ppwfxInfo)->cbSize)) + sizeof(WORD)),cbExtraBytes) != cbExtraBytes)
		{
			delete *ppwfxInfo;
			*ppwfxInfo = NULL;
			return E_FAIL;
		}
	}
	if (mmioAscend(hmmioIn,&ckIn,0))
	{
		delete *ppwfxInfo;
		*ppwfxInfo = NULL;
		return E_FAIL;
	}
	return S_OK;
}

