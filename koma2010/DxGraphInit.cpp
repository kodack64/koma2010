#include	"dx8.h"

int CDirectX::Direct3DInit(HWND hwnd,int FULLSCREEN,int WIDTH,int HEIGHT,DIALOG_STATE pds)
{
	//�_�C�A���O�̐ݒ���R�s�[
	ds=pds;
	// Direct3D �I�u�W�F�N�g���쐬
	lpD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// �I�u�W�F�N�g�쐬���s
		MessageBox(NULL,"Direct3D �̍쐬�Ɏ��s���܂����B","error",MB_OK | MB_ICONSTOP);
		WriteLog("  Direct3D �̍쐬�Ɏ��s���܂���");
		// �I������
		return -1;
	}
	adapter = 0;

	// �E�C���h�E�̍쐬�����������̂ŁADirect3D ������������
	ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));
	// ���݂̉�ʃ��[�h���擾
	lpD3D->GetAdapterDisplayMode(adapter,&disp);
	// Direct3D �������p�����[�^�̐ݒ�
	if (FULLSCREEN)
	{
		// �t���X�N���[�� : �قƂ�ǂ̃A�_�v�^�ŃT�|�[�g����Ă���t�H�[�}�b�g���g�p
//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// �E�C���h�E : ���݂̉�ʃ��[�h���g�p
		d3dpp.BackBufferFormat = disp.Format;
	}
	// �\���̈�T�C�Y�̐ݒ�
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	if (!FULLSCREEN)
	{
		// �E�C���h�E���[�h
		d3dpp.Windowed = 1;
	}
	// Z �o�b�t�@�̎����쐬
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	param = d3dpp;

//	WriteLog(" �f�o�C�X���쐬���܂�");
	// �f�o�C�X�̍쐬 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDEV)))
	{
		// ���s�����̂� HAL �Ŏ��s
		if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDEV)))
		{
			// ���s�����̂� REF �Ŏ��s
			if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDEV)))
			{
				// ���ǎ��s����
				MessageBox(NULL,"Direct3D �̏������Ɏ��s���܂����B","error",MB_OK | MB_ICONSTOP);
				WriteLog("  �f�o�C�X�̍쐬�Ɏ��s���܂���");
				RELEASE(lpD3D);
				// �I������
				return -1;
			}
//			else	WriteLog("REF�ŋN�����܂�");
		}
//		else	WriteLog("HAL�ŋN�����܂�");
	}
//	else	WriteLog("T&L HAL�ŋN�����܂�");

	hFont = CreateFont( 
		14, 0, 0, 0,FW_REGULAR,FALSE,FALSE,FALSE,
		SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
		"�l�r �o�S�V�b�N" 
	);
	D3DXCreateFont( lpD3DDEV , hFont , &lpFont ) ;
	DeleteObject(hFont);

	D3DXCreateSprite(lpD3DDEV, &lpD3DXSprite );

	lpD3DDEV->SetRenderState (D3DRS_ZENABLE,TRUE) ;
	lpD3DDEV->SetRenderState (D3DRS_LIGHTING,FALSE) ;

	lpD3DDEV->SetRenderState (D3DRS_ALPHABLENDENABLE,TRUE) ;
	lpD3DDEV->SetRenderState (D3DRS_SRCBLEND,D3DBLEND_ONE) ;
//	lpD3DDEV->SetRenderState (D3DRS_DESTBLEND,D3DBLEND_ONE) ;
	lpD3DDEV->SetRenderState (D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA) ;

	lpD3DDEV->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);

	lpD3DDEV->SetTextureStageState (0,D3DTSS_ALPHAOP,D3DTOP_MODULATE) ;
	lpD3DDEV->SetTextureStageState (0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE) ;
	lpD3DDEV->SetTextureStageState (0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE) ;

	lpD3DDEV->SetTextureStageState (0,D3DTSS_COLOROP,D3DTOP_MODULATE) ;
	lpD3DDEV->SetTextureStageState (0,D3DTSS_COLORARG1,D3DTA_TEXTURE) ;
	lpD3DDEV->SetTextureStageState (0,D3DTSS_COLORARG2,D3DTA_DIFFUSE) ;
	return 0;
}