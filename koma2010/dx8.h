#ifndef	CDIRECTX_H
#define	CDIRECTX_H

#define DIRECTINPUT_VERSION 0x0800

#include	"function.h"	//ヘッダその他
#include	"graph.h"		//DirectGraphic
#include	"audio.h"		//DirectAudio
#include	"show.h"		//DirectShow
#include	"mouse.h"		//Mouse
#include	"key.h"			//Key
#include	"b2object_states.h"	//test

class	CDirectX
{
private:
	D3DPRESENT_PARAMETERS param;
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE disp;
	LPDIRECT3D8 lpD3D;
	LPDIRECT3DDEVICE8 lpD3DDEV;
	LPD3DXSPRITE	lpD3DXSprite;

	LPD3DXFONT lpFont ;
	HFONT hFont ;

	LPDIRECTSOUND8 lpDS;
	LPDIRECTSOUNDBUFFER lpDSP;
	LPDIRECTSOUND3DLISTENER lpListener;

	vector	< Graph *> graph;
	vector	< Audio *> audio;
	vector	< Audio *> audio_dup;
	vector	< Show *> show;

	HINTERNET hInternet;
	HINTERNET hHost;

	DIALOG_STATE ds;

	bool colorkey;
	int r,g,b;

	bool network;			//スコアサーバー接続状況

	int adapter;

	int br,bg,bb;

	int strr,strg,strb,stra;
	int scrslidex,scrslidey;

	float scrr,scrg,scrb,scrl;

	DWORD BeginTime;


public:
	////////////////////////////////
	/*コンストラクタ・デストラクタ*/
	////////////////////////////////
	CDirectX();
	virtual ~CDirectX();

	////////////////////
	/*全般の初期化関連*/
	////////////////////
	virtual int Direct3DInit(HWND hwnd,int wid,int hei,int full,DIALOG_STATE pds);	//Direct3Dの初期化
	virtual int DirectAudioInit(HWND hwnd);							//DirectAudioの初期化
	virtual int DirectShowInit(HWND hwnd);							//DirectShowの初期化

	//////////////////////////
	/*起動時のダイアログ関連*/
	//////////////////////////
	virtual void SetDialogState(DIALOG_STATE sds);//ダイアログの状態を更新する

	////////////
	/*描画関連*/
	////////////
	virtual void DrawBegin();			//描画の設定
	virtual void DrawEnd();				//ディスプレイに表示
	virtual void SetColorKey(bool,int,int,int);	//カラーキーを設定
	virtual void SetBackScreenColor(int,int,int);	//バックスクリーンの色を設定
	virtual void SetScreenColor(float red,float green,float blue,float light);//スクリーンの配色を設定
	virtual int LoadGraph(const char*);			//画像をロード
	virtual void SetSlideDrawScreenCenter(int x,int y);	//画面の描画をずらす数値
	virtual void SetGraphColor(unsigned int number,float red,float green,float blue,float light);	//明るさを設定
	virtual void SetGraphCenter(unsigned int number,bool flag,int x,int y);	//画像を回転させるときの中央を設定
	virtual void DrawGraph(int x,int y,int wid,int hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number);	//通常描画
	virtual void DrawGraph(int x,int y,int wid,int hei,int gx,int gy,int gwid,int ghei,unsigned int number);	//通常描画
	virtual void DrawGraph(float x,float y,float wid,float hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number);	//通常描画
	virtual void DrawGraph(float x,float y,float wid,float hei,int gx,int gy,int gwid,int ghei,unsigned int number);	//通常描画
	virtual void DrawGraph(float x,float y,int wid,int hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number);	//通常描画
	virtual void DrawGraph(float x,float y,int wid,int hei,int gx,int gy,int gwid,int ghei,unsigned int number);	//通常描画
	virtual void DrawGraph(int x,int y,int wid,int hei,int gx,int gy,unsigned int number);	//通常描画
	virtual void DrawGraphSprite(int x,int y,int gx,int gy,int wid,int hei,float a,float b,int rad,unsigned int number);	//描画
	virtual void DrawString(char*,int x,int y);	//文字列を描画
	virtual int SetStringFont(char *fontname,int size);	//フォントを設定
	virtual void SetStringColor(int r,int g,int b,int a);//文字列の色を指定
	virtual void ClearScreen();					//スクリーンを消す
	virtual void MoveMatrix(LPTLVERTEX v, float x, float y, float z);	//移動行列
	virtual void ZoomMatrix(LPTLVERTEX v, float x, float y, float z);	//拡大行列
	virtual void RotateMatrix(LPTLVERTEX v, int Rotate);				//回転行列

	/////////////
	/*Box2D関連*/
	/////////////
	b2World* world;
	virtual b2Body* b2CreateBox(float x,float y,float wid,float hei,float ldump,float rdump,float density,float fric,float rest,bool dynamic,bool sensor,b2State* st);
	virtual b2Body* b2CreateCircle(float x,float y,float r,float ldump,float rdump,float density,float fric,float rest,bool dynamic,bool sensor,b2State* st);
	virtual b2Body* b2CreatePolygon(float x,float y,b2Vec2* poly,int vernum ,float ldump,float rdump,float density,float fric,float rest,bool dynamic,bool sensor,b2State* st);


	///////////
	/*Wav再生*/
	///////////
	virtual int LoadWav(char*);					//Wavファイルを2D音源として読み込む
	virtual int LoadWavEx(char*);				//Wavファイルを3D音源として読み込む
	virtual void PlayWav(unsigned int number,float x,float y,int volume,Music_State state);		//Wavを再生
	virtual int PlayNewWav(unsigned int number,float x,float y,int volume,Music_State state);	//既に読み込んだWavで新しく再生
	virtual int DeleteDuplicatedWav();	//複製したWavを削除

	////////////////////////
	/*音楽再生(DirectShow)*/
	////////////////////////
	virtual int LoadMusic(char*);									//DirectShowを使ってMp3を読み込む
	virtual void PlayMusic(unsigned int number,Music_State state);	//DirectShowを使ってMp3を再生
	virtual int SetSpeed(unsigned int number,double speed);			//再生スピードの変更

	////////////
	/*時間関連*/
	////////////
	virtual void SetBeginTime(void);		//ゲーム開始時刻を指定
	virtual float GetGameTime(void);		//ゲーム開始からの時刻を取得

	//////////////////////
	/*ポインタを返す関数*/
	//////////////////////
	LPDIRECT3D8			GetDirect3D()
	{
		return lpD3D;
	}
	LPDIRECT3DDEVICE8	GetDirect3DDev()
	{
		return lpD3DDEV;
	}
	LPDIRECTSOUND8		GetDirectSound()
	{
		return	lpDS;
	}
	LPDIRECTSOUNDBUFFER GetDirectSoundBuf()
	{
		return lpDSP;
	}
	LPDIRECTSOUND3DLISTENER GetDirectSoundLis()
	{
		return lpListener;
	}
};

#endif	CDIRECTX_H