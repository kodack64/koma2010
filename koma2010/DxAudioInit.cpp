#include	"dx8.h"

int CDirectX::DirectAudioInit(HWND hwnd)
{
	// DirectSound8 �̍쐬
	if (FAILED(DirectSoundCreate8(NULL,&lpDS,NULL)))
	{
		MessageBox(NULL,"DirectSound �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����B","error",MB_OK | MB_ICONSTOP);
		WriteLog(" DirectSound �I�u�W�F�N�g�̍쐬�Ɏ��s���܂���");
		return -1;
	}
	// DirectSound �̋������x����ݒ�
	if (FAILED(lpDS->SetCooperativeLevel(hwnd,DSSCL_PRIORITY)))
	{
		MessageBox(NULL,"DirectSound �̋������x���̐ݒ�Ɏ��s���܂����B","error",MB_OK | MB_ICONSTOP);
		WriteLog(" DirectSound �̋������x���̐ݒ�Ɏ��s���܂���");
		return -1;
	}
	// �v���C�}�� �T�E���h�o�b�t�@�쐬
	DSBUFFERDESC desc;
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSP,NULL)))
	{
		MessageBox(NULL,"�v���C�}���T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂����B","error",MB_OK | MB_ICONSTOP);
		WriteLog(" �v���C�}���T�E���h�o�b�t�@�̍쐬�Ɏ��s���܂���");
		return -1;
	}
	// �v���C�}���o�b�t�@���烊�X�i�[���擾
	if (FAILED(lpDSP->QueryInterface(IID_IDirectSound3DListener,(void **)&lpListener)))
	{
		MessageBox(NULL,"���X�i�[�̍쐬�Ɏ��s���܂����B","error",MB_OK | MB_ICONSTOP);
		WriteLog(" ���X�i�[�̍쐬�Ɏ��s���܂���");
		return -1;
	}
	// ���X�i�[�̃p�����[�^�̐ݒ�
	lpListener->SetPosition(0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
	lpListener->SetVelocity(0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
	lpListener->SetOrientation(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
	return 0;
}
