#include	"dx8.h"

void CDirectX::SetDialogState(DIALOG_STATE sds)
{
	ds=sds;
}

//CDirectX�N���X�@�R���X�g���N�^
CDirectX::CDirectX():
lpD3D(NULL),
lpD3DDEV(NULL),
lpDS(NULL),
lpDSP(NULL),
lpListener(NULL),
lpFont(NULL),
hInternet(NULL),
colorkey(false),
br(0),bg(0),bb(0),
scrr(1),scrg(1),scrb(1),scrl(1),
strr(0xFF),strg(0xFF),strb(0xFF),stra(0xFF)
{
}

//CDirectX�N���X�@�f�X�g���N�^
CDirectX::~CDirectX()
{
	// COM �I��
	CoUninitialize();

	//�e�s�o�T�[�o�ؒf
//	NetClose();

	//CDirectX�N���X���ێ�����e�N���X�����
	int loop;
	for(loop=0;loop<graph.size();loop++)
	{
		SAFE_DELETE(graph[loop]);
	}
	for(loop=0;loop<audio.size();loop++)
	{
		SAFE_DELETE(audio[loop]);
	}
	for(loop=0;loop<audio_dup.size();loop++)
	{
		SAFE_DELETE(audio_dup[loop]);
	}
	for(loop=0;loop<show.size();loop++)
	{
		SAFE_DELETE(show[loop]);
	}
	// �쐬�����I�u�W�F�N�g�̊J��
	RELEASE(lpD3DXSprite);
	RELEASE(lpD3DDEV);
	RELEASE(lpD3D);

	RELEASE(lpDSP);
	RELEASE(lpDS);

	RELEASE(lpFont);
}