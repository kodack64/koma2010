#include	"game.h"


Game::Game()
{}

Game::~Game()
{
	SAFE_DELETE(menu);
	SAFE_DELETE(tap);
}

int Game::Init(CDirectX* cdx)
{
	dx=cdx;
	dx->SetBackScreenColor(0xff,0xff,0xff);
	key.SetKeyState();
	mouse.SetMouse();

	//Write Init Process
	menu = new Menu;
	menu->Init(dx,&mouse,&key);
	tap = new Tap;
	tap->Init(dx,&mouse,&key);

	Reset();

	return 0;
}

int Game::Main()
{
	//インターフェイスの状態を更新
	key.SetKeyState();
	mouse.SetMouse();

	//Write Game Process;
	switch(gs){
	case ST_MENU:
		ProcMenu();
		break;
	case ST_TAP:
		ProcTap();
		break;
	case ST_TUTORIAL:
		break;
	case ST_RESULT:
		ProcResult();
		break;
	case ST_REPLAY:
		break;
	case ST_END:
		return -1;
		break;
	default:
		assert(false);
		break;
	}


	if(key.GetKey(VK_ESCAPE)==true){
		Reset();
//		return -1;
	}
	return 0;
}

int Game::Draw()
{
	dx->ClearScreen();
	dx->DrawBegin();

	//Write Draw Process
	switch(gs){
	case ST_MENU:
		menu->Draw();
		break;
	case ST_TAP:
		tap->Draw();
		break;
	case ST_TUTORIAL:
		break;
	case ST_RESULT:
		break;
	case ST_REPLAY:
		break;
	case ST_END:
		break;
	default:
		assert(false);
		break;
	}

	dx->DrawEnd();
	return 0;
}