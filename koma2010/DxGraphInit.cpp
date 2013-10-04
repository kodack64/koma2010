#include	"dx8.h"

int CDirectX::Direct3DInit(HWND hwnd,int FULLSCREEN,int WIDTH,int HEIGHT,DIALOG_STATE pds)
{
	//ダイアログの設定をコピー
	ds=pds;
	// Direct3D オブジェクトを作成
	lpD3D = Direct3DCreate8(D3D_SDK_VERSION);
	if (!lpD3D)
	{
		// オブジェクト作成失敗
		MessageBox(NULL,"Direct3D の作成に失敗しました。","error",MB_OK | MB_ICONSTOP);
		WriteLog("  Direct3D の作成に失敗しました");
		// 終了する
		return -1;
	}
	adapter = 0;

	// ウインドウの作成が完了したので、Direct3D を初期化する
	ZeroMemory(&d3dpp,sizeof(D3DPRESENT_PARAMETERS));
	// 現在の画面モードを取得
	lpD3D->GetAdapterDisplayMode(adapter,&disp);
	// Direct3D 初期化パラメータの設定
	if (FULLSCREEN)
	{
		// フルスクリーン : ほとんどのアダプタでサポートされているフォーマットを使用
//		d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
		d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	}
	else
	{
		// ウインドウ : 現在の画面モードを使用
		d3dpp.BackBufferFormat = disp.Format;
	}
	// 表示領域サイズの設定
	d3dpp.BackBufferWidth = WIDTH;
	d3dpp.BackBufferHeight = HEIGHT;
	d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
	if (!FULLSCREEN)
	{
		// ウインドウモード
		d3dpp.Windowed = 1;
	}
	// Z バッファの自動作成
	d3dpp.EnableAutoDepthStencil = 1;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	param = d3dpp;

//	WriteLog(" デバイスを作成します");
	// デバイスの作成 - T&L HAL
	if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDEV)))
	{
		// 失敗したので HAL で試行
		if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_HAL,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDEV)))
		{
			// 失敗したので REF で試行
			if (FAILED(lpD3D->CreateDevice(adapter,D3DDEVTYPE_REF,hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp,&lpD3DDEV)))
			{
				// 結局失敗した
				MessageBox(NULL,"Direct3D の初期化に失敗しました。","error",MB_OK | MB_ICONSTOP);
				WriteLog("  デバイスの作成に失敗しました");
				RELEASE(lpD3D);
				// 終了する
				return -1;
			}
//			else	WriteLog("REFで起動します");
		}
//		else	WriteLog("HALで起動します");
	}
//	else	WriteLog("T&L HALで起動します");

	hFont = CreateFont( 
		14, 0, 0, 0,FW_REGULAR,FALSE,FALSE,FALSE,
		SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
		"ＭＳ Ｐゴシック" 
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