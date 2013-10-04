#include	"dx8.h"

int CDirectX::DirectAudioInit(HWND hwnd)
{
	// DirectSound8 の作成
	if (FAILED(DirectSoundCreate8(NULL,&lpDS,NULL)))
	{
		MessageBox(NULL,"DirectSound オブジェクトの作成に失敗しました。","error",MB_OK | MB_ICONSTOP);
		WriteLog(" DirectSound オブジェクトの作成に失敗しました");
		return -1;
	}
	// DirectSound の協調レベルを設定
	if (FAILED(lpDS->SetCooperativeLevel(hwnd,DSSCL_PRIORITY)))
	{
		MessageBox(NULL,"DirectSound の協調レベルの設定に失敗しました。","error",MB_OK | MB_ICONSTOP);
		WriteLog(" DirectSound の協調レベルの設定に失敗しました");
		return -1;
	}
	// プライマリ サウンドバッファ作成
	DSBUFFERDESC desc;
	ZeroMemory(&desc,sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
	if (FAILED(lpDS->CreateSoundBuffer(&desc,&lpDSP,NULL)))
	{
		MessageBox(NULL,"プライマリサウンドバッファの作成に失敗しました。","error",MB_OK | MB_ICONSTOP);
		WriteLog(" プライマリサウンドバッファの作成に失敗しました");
		return -1;
	}
	// プライマリバッファからリスナーを取得
	if (FAILED(lpDSP->QueryInterface(IID_IDirectSound3DListener,(void **)&lpListener)))
	{
		MessageBox(NULL,"リスナーの作成に失敗しました。","error",MB_OK | MB_ICONSTOP);
		WriteLog(" リスナーの作成に失敗しました");
		return -1;
	}
	// リスナーのパラメータの設定
	lpListener->SetPosition(0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
	lpListener->SetVelocity(0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
	lpListener->SetOrientation(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,DS3D_IMMEDIATE);
	return 0;
}
