#define STRICT

#include	"dx8.h"
#include	"appli.h"
#include	"resource.h"

const char g_szClassName[]="FLICKER";
const char g_szWindowName[]="FLICKER";

#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define	WIDTH			640
#define	HEIGHT			480
#define Def_FPS			60
#define	FULLSCREEN		0
#define DEBUGMEM		1

CDirectX	*dx;
Appli	*appli;

HWND	hwnd;
int endf;
char dir[MAX_PATH];
FILE *fp_log;
int VER;
int RUNFIRST;
int FPS;
int Connect;
int WINDOWMODE;
int DevelopMode;
char HostServer[MAX_PATH];
char HostName[MAX_PATH];
char HostPass[MAX_PATH];
char PlayerName[MAX_NAME];
char PlayerPass[MAX_PASS];
DIALOG_STATE ds;
void LoadInitialSettings(DIALOG_STATE *ds);

void MainLoop(HWND hwnd);

HINSTANCE	g_hinstSelf;

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int PASCAL WinMain(HINSTANCE hInst,HINSTANCE hPrev,char *CmdLine,int CmdShow)
{
	GetCurrentDirectory(MAX_PATH,dir);

	if(DEBUGMEM){
//		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
//		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
//		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	}

	LoadInitialSettings(&ds);

	int width,height;

	if(ds.LOG==1) fp_log=fopen("Log.txt","w");
	else fp_log=NULL;
	if(fp_log!=NULL)
	{
		fprintf(fp_log,"%s\n",g_szClassName);
		fprintf(fp_log,"���O�L�^���J�n���܂�\n");
	}
	else if(ds.LOG==1)
	{
		MessageBox(NULL,"���O�̋L�^�Ɏ��s���܂���","error",MB_OK);
	}
	setlocale( LC_ALL, "" );

	appli=new Appli;
	dx=new CDirectX;
	endf=0;
	g_hinstSelf=hInst;

	if((hwnd=FindWindow(g_szClassName,g_szWindowName))!=NULL)
	{
		MessageBox(NULL,"���ɋN�����Ă��܂�","error",MB_OK);
		return 0;
	}
	SeparateLog();

	WriteLog("�E�B���h�E�̍쐬...");
	WNDCLASSEX	wcex;
	ZeroMemory(&wcex,sizeof(WNDCLASS));

	wcex.cbSize			=	sizeof(WNDCLASSEX);
	wcex.style			=	0;
	wcex.lpfnWndProc	=	WndProc;
	wcex.cbClsExtra		=	0;
	wcex.cbWndExtra		=	0;
	wcex.hIcon			=	LoadIcon(hInst, "ICON");
	wcex.hIconSm		=	LoadIcon(hInst, "ICON");
	wcex.hbrBackground	=	(HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName	=	NULL;
	wcex.lpszClassName	=	g_szClassName;
	wcex.hbrBackground	=	(HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor		=	LoadCursor(NULL,IDC_ARROW);
	wcex.hInstance		=	hInst;
	if(RegisterClassEx(&wcex)==0)
	{
		WriteLog(" �쐬�Ɏ��s");
		return FALSE;
	}
	if (ds.WINDOWMODE==1)
	{
//		WriteLog("�t���X�N���[���ŋN��");
		width = WIDTH;
		height = HEIGHT;
		hwnd = CreateWindow(
			g_szClassName,
			g_szWindowName,
			WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			NULL,
			NULL,
			hInst,
			NULL);
		if(hwnd==NULL)
		{
			WriteLog(" �E�B���h�E�̍쐬�Ɏ��s");
			return FALSE;
		}
	}
	else
	{
//		WriteLog("�E�B���h�E���[�h�ŋN��");
		width = WIDTH + GetSystemMetrics(SM_CXDLGFRAME) * 2;
		height = HEIGHT + GetSystemMetrics(SM_CYDLGFRAME) * 2 +GetSystemMetrics(SM_CYCAPTION);
		hwnd = CreateWindow(
			g_szClassName,
			g_szWindowName,
			WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			NULL,
			NULL,
			hInst,
			NULL);
		if(hwnd==NULL)
		{
			WriteLog(" �E�B���h�E�̍쐬�Ɏ��s");
			return FALSE;
		}
	}
//	WriteLog("�E�B���h�E���쐬");

	WINDOWMODE=ds.WINDOWMODE;

	dx->SetDialogState(ds);

	WriteLog("DirectX��������...");
	WriteLog(" Direct3D��������...");
	if(WINDOWMODE!=0)	dx->Direct3DInit(hwnd,1,WIDTH,HEIGHT,ds);
	else				dx->Direct3DInit(hwnd,0,WIDTH,HEIGHT,ds);
	WriteLog(" DirectAudio�̏�����...");
	dx->DirectAudioInit(hwnd);
	WriteLog(" DirectShow�̏�����...");
	dx->DirectShowInit(hwnd);
//	WriteLog("DirectX�̏������ɐ���");
//	SeparateLog();

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);


	MainLoop(hwnd);
	return 0;
}

void MainLoop(HWND hwnd)
{
	MSG msg;
	DWORD	dwBegin,dwNow;

	char time[256];
	char log[256];
	char str[256];
	double ShowFps=0;
	double SetFps = (1000.0f/Def_FPS) ;
	bool mousest=false;
	int fps=0;

	timeBeginPeriod( 1 ) ;
	
	WriteLog("�A�v���P�[�V������������...");
	int apres=appli->Init(dx);
//	WriteLog("���������܂���");

	GetTimeFormat(LOCALE_SYSTEM_DEFAULT,NULL,NULL,"hh' �� 'm' �� 's' �b '" ,time,30);
	sprintf(log,"%s�ɊJ�n",time);
	WriteLog(log);

	RECT rc;
	GetWindowRect(hwnd, &rc);
	
	dwBegin = timeGetTime() ;
	while(endf==0 && apres!=-1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE))
		{
			if(!GetMessage(&msg,NULL,0,0)) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(GetActiveWindow()==hwnd)
		{
			if(mousest==true)
			{
				mousest=false;
				ShowCursor(false);
			}
			dwNow=timeGetTime();
			if ( dwNow - dwBegin  > SetFps*fps )
			{
				if(fps>=Def_FPS){
					if(WINDOWMODE==0)
					{
						sprintf(str,"%s  FPS %d",g_szWindowName,(int)(1000/((double)(dwNow-dwBegin)/Def_FPS)));
						SetWindowText(hwnd,str);
					}
					fps=0;
					dwBegin=dwNow;
				}
				fps++;

				if(appli->Main()==-1)break;
				appli->Draw();

				InvalidateRgn(hwnd,NULL,FALSE);
				UpdateWindow(hwnd);
			}
		}
		else
		{
			ClipCursor(NULL);
			if(mousest==false)
			{
				mousest=true;
				ShowCursor(true);
			}
		}
	}
	timeEndPeriod( 1 ) ;
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT,NULL,NULL,"hh' �� 'm' �� 's' �b '" ,time,30);
	sprintf(log,"%s�ɏI��",time);

	delete	appli;
	delete	dx;
	WriteLog("�I�u�W�F�N�g��������܂���");
	WriteLog(log);
	SeparateLog();
	timeEndPeriod( 1 ) ;
	WriteLog("���O�ۑ����I�����܂�");
	if(ds.LOG==1 && fp_log!=NULL) fclose(fp_log);
}

LRESULT	CALLBACK	WndProc
(
	HWND	hwnd,
	UINT	uiMessage,
	WPARAM	wparam,
	LPARAM	lparam
)
{
	switch(uiMessage)
	{
		case WM_COMMAND:
			switch(LOWORD(wparam))
			{
			case IDM_END:
				SendMessage(hwnd,WM_CLOSE,0,0L);
				break;
			}
			return 0;
		case WM_CLOSE:
			SeparateLog();
			WriteLog("�I�����閽�߂��o����܂���");
			SendMessage(hwnd,WM_DESTROY,0,0L);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			endf=1;
			return 0;
		default:
			break;
	}
	return DefWindowProc(hwnd,uiMessage,wparam,lparam);
}

char* GetMyDir()	{return dir;}

HWND GetWindowHandle()	{return hwnd;}

void WriteLog(char *str)
{
	char log[256];
	sprintf(log,"%s \n",str);
	if(fp_log!=NULL)
	{
		fprintf(fp_log,log);
	}
}

void SeparateLog(){
	if(fp_log!=NULL)
	{
		fprintf(fp_log,"------------------------------------\n");
	}
}

RECT GetMyRect()
{
	RECT rc;
	GetWindowRect(GetWindowHandle(),&rc);
	if(ds.WINDOWMODE==0)
	{
		rc.left+=GetSystemMetrics(SM_CXDLGFRAME);
		rc.top+=GetSystemMetrics(SM_CXDLGFRAME)+GetSystemMetrics(SM_CYCAPTION);
	}
	return rc;
}

void LoadInitialSettings(DIALOG_STATE *ds){
	ds->WINDOWMODE=GetPrivateProfileInt("system","WINDOWMODE",0,"./setup.ini");
	ds->LOG=GetPrivateProfileInt("system","LOG",0,"./setup.ini");
}

void GetGameName(char* str){
	strcpy(str,g_szClassName);
}

int round(double x){
	int i=(int)x;
	if(x-i<0.5f){
		return i;
	}else{
		return i+1;
	}
}