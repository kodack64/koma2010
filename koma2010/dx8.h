#ifndef	CDIRECTX_H
#define	CDIRECTX_H

#define DIRECTINPUT_VERSION 0x0800

#include	"function.h"	//�w�b�_���̑�
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

	bool network;			//�X�R�A�T�[�o�[�ڑ���

	int adapter;

	int br,bg,bb;

	int strr,strg,strb,stra;
	int scrslidex,scrslidey;

	float scrr,scrg,scrb,scrl;

	DWORD BeginTime;


public:
	////////////////////////////////
	/*�R���X�g���N�^�E�f�X�g���N�^*/
	////////////////////////////////
	CDirectX();
	virtual ~CDirectX();

	////////////////////
	/*�S�ʂ̏������֘A*/
	////////////////////
	virtual int Direct3DInit(HWND hwnd,int wid,int hei,int full,DIALOG_STATE pds);	//Direct3D�̏�����
	virtual int DirectAudioInit(HWND hwnd);							//DirectAudio�̏�����
	virtual int DirectShowInit(HWND hwnd);							//DirectShow�̏�����

	//////////////////////////
	/*�N�����̃_�C�A���O�֘A*/
	//////////////////////////
	virtual void SetDialogState(DIALOG_STATE sds);//�_�C�A���O�̏�Ԃ��X�V����

	////////////
	/*�`��֘A*/
	////////////
	virtual void DrawBegin();			//�`��̐ݒ�
	virtual void DrawEnd();				//�f�B�X�v���C�ɕ\��
	virtual void SetColorKey(bool,int,int,int);	//�J���[�L�[��ݒ�
	virtual void SetBackScreenColor(int,int,int);	//�o�b�N�X�N���[���̐F��ݒ�
	virtual void SetScreenColor(float red,float green,float blue,float light);//�X�N���[���̔z�F��ݒ�
	virtual int LoadGraph(const char*);			//�摜�����[�h
	virtual void SetSlideDrawScreenCenter(int x,int y);	//��ʂ̕`������炷���l
	virtual void SetGraphColor(unsigned int number,float red,float green,float blue,float light);	//���邳��ݒ�
	virtual void SetGraphCenter(unsigned int number,bool flag,int x,int y);	//�摜����]������Ƃ��̒�����ݒ�
	virtual void DrawGraph(int x,int y,int wid,int hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number);	//�ʏ�`��
	virtual void DrawGraph(int x,int y,int wid,int hei,int gx,int gy,int gwid,int ghei,unsigned int number);	//�ʏ�`��
	virtual void DrawGraph(float x,float y,float wid,float hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number);	//�ʏ�`��
	virtual void DrawGraph(float x,float y,float wid,float hei,int gx,int gy,int gwid,int ghei,unsigned int number);	//�ʏ�`��
	virtual void DrawGraph(float x,float y,int wid,int hei,int gx,int gy,int gwid,int ghei,int rot,float zoom,unsigned int number);	//�ʏ�`��
	virtual void DrawGraph(float x,float y,int wid,int hei,int gx,int gy,int gwid,int ghei,unsigned int number);	//�ʏ�`��
	virtual void DrawGraph(int x,int y,int wid,int hei,int gx,int gy,unsigned int number);	//�ʏ�`��
	virtual void DrawGraphSprite(int x,int y,int gx,int gy,int wid,int hei,float a,float b,int rad,unsigned int number);	//�`��
	virtual void DrawString(char*,int x,int y);	//�������`��
	virtual int SetStringFont(char *fontname,int size);	//�t�H���g��ݒ�
	virtual void SetStringColor(int r,int g,int b,int a);//������̐F���w��
	virtual void ClearScreen();					//�X�N���[��������
	virtual void MoveMatrix(LPTLVERTEX v, float x, float y, float z);	//�ړ��s��
	virtual void ZoomMatrix(LPTLVERTEX v, float x, float y, float z);	//�g��s��
	virtual void RotateMatrix(LPTLVERTEX v, int Rotate);				//��]�s��

	/////////////
	/*Box2D�֘A*/
	/////////////
	b2World* world;
	virtual b2Body* b2CreateBox(float x,float y,float wid,float hei,float ldump,float rdump,float density,float fric,float rest,bool dynamic,bool sensor,b2State* st);
	virtual b2Body* b2CreateCircle(float x,float y,float r,float ldump,float rdump,float density,float fric,float rest,bool dynamic,bool sensor,b2State* st);
	virtual b2Body* b2CreatePolygon(float x,float y,b2Vec2* poly,int vernum ,float ldump,float rdump,float density,float fric,float rest,bool dynamic,bool sensor,b2State* st);


	///////////
	/*Wav�Đ�*/
	///////////
	virtual int LoadWav(char*);					//Wav�t�@�C����2D�����Ƃ��ēǂݍ���
	virtual int LoadWavEx(char*);				//Wav�t�@�C����3D�����Ƃ��ēǂݍ���
	virtual void PlayWav(unsigned int number,float x,float y,int volume,Music_State state);		//Wav���Đ�
	virtual int PlayNewWav(unsigned int number,float x,float y,int volume,Music_State state);	//���ɓǂݍ���Wav�ŐV�����Đ�
	virtual int DeleteDuplicatedWav();	//��������Wav���폜

	////////////////////////
	/*���y�Đ�(DirectShow)*/
	////////////////////////
	virtual int LoadMusic(char*);									//DirectShow���g����Mp3��ǂݍ���
	virtual void PlayMusic(unsigned int number,Music_State state);	//DirectShow���g����Mp3���Đ�
	virtual int SetSpeed(unsigned int number,double speed);			//�Đ��X�s�[�h�̕ύX

	////////////
	/*���Ԋ֘A*/
	////////////
	virtual void SetBeginTime(void);		//�Q�[���J�n�������w��
	virtual float GetGameTime(void);		//�Q�[���J�n����̎������擾

	//////////////////////
	/*�|�C���^��Ԃ��֐�*/
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