#ifndef	KYODO_H
#define	KYODO_H

#define	WIN32_LEAN_AND_MEAN
#define WM_NETPLAY	(WM_USER+1)
#define WM_GRAPHNOTIFY	(WM_USER+2)
#define DIRECTINPUT_VERSION 0x0800
#define _CRTDBG_MAP_ALLOC

#pragma warning(disable:4018)
#pragma warning(disable:4244)
#pragma warning(disable:4995)
#pragma warning(disable:4996)

#pragma comment(lib, "d3d8.lib")
#pragma comment(lib, "d3dx8.lib")
#pragma comment(lib, "dinput.lib")
#pragma comment(lib, "ddraw.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxerr8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "strmiids.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "wininet.lib")

/* Debug�̏ꍇ */
#ifdef _DEBUG
#pragma comment(lib, "Box2D_d.lib")
//#pragma comment(linker, "/NODEFAULTLIB:LIBCMTD.lib")

/* Release�̏ꍇ */
#else
#pragma comment(lib, "Box2D.lib")
//#pragma comment(linker, "/NODEFAULTLIB:LIBCMT.lib")
#endif

#include	<windows.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	<time.h>
#include	<math.h>
#include	<assert.h>
#include	<commctrl.h>
#include	<mmsystem.h>
#include    <crtdbg.h>

#include	<wininet.h>
#include	<winsock2.h>

#include	<d3d8.h>
#include	<d3dx8.h>
#include	<dsound.h>
#include	<dmusicc.h>
#include	<dmusici.h>
#include	<dinput.h>
#include	<dshow.h>
#include	<dmodshow.h>
#include	<dplay8.h>
#include	<locale.h>
#include	<dxerr8.h>

#include	<Box2D/Box2D.h>

#include	<string>
#include	<vector>
#include	<list>
#include	<algorithm>
using namespace std;

#define	RELEASE(o)	if (o){o->Release();o=NULL;}
#define	SAFE_DELETE(p)	if(p){delete []p;p=NULL;}
#define SAFE_DELETE_ARRAY( p )	if( p ){ delete[] ( p ); ( p ) = NULL; }
#define	FVF_TLVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define	GRAPH_DEF	0
#define	MAX_DATA		1000
#define	MAX_CHAT		50
#define	MAX_MESSAGE		100
#define	MAX_PLAYER		100
#define MAX_NAME 50
#define MAX_IP 20
#define	MAX_PASS	30
#define FONT_SIZE	14
#define PI 3.14159265f

typedef struct _TLVERTEX
{
	float x,y,z;
	float rhw;
	D3DCOLOR color;
	float tu,tv;
}TLVERTEX,*LPTLVERTEX;


typedef struct{
  char         cRIFF[4];
  int          iSizeRIFF;
  char         cType[4];
  char         cFmt[4];
  int          iSizeFmt;
  WAVEFORMATEX WaveFmt;
  char         cData[4];
  int          iSizeData;
} WAVEFILEHEADER;

struct	JoypadState
{
	int StickX;
	int StickY;
	int StickZ;
	int StickRollX;
	int StickRollY;
	int StickRollZ;
	bool button[31];
};

typedef enum
{
	Play,
	Stop,
	Rewind,
	Play_Loop,
	Replay,
	Close
}Music_State;

struct	DIALOG_STATE
{
	int LOG;
	int WINDOWMODE;
};

char* GetMyDir();
RECT GetMyRect();
void GetGameName(char*);
HWND GetWindowHandle();
void WriteLog(char *str);
void SeparateLog();
bool WriteSave(char *name,char *str);
bool LoadSave(char *name,int type);
LRESULT	CALLBACK DlgProc(HWND,UINT,WPARAM,LPARAM);
int round(double);

#endif	KYODO_H