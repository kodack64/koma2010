#include	"appli.h"

#define MAX_GAME 1

Appli::Appli()
{
}

Appli::~Appli()
{
	SAFE_DELETE(game);
}

int Appli::Main()
{
	if(game->Main()==-1){
		return -1;
	}
	return 0;
}

int Appli::Draw()
{
	game->Draw();
	return 0;
}

int Appli::Init(CDirectX *directx)
{
	srand((unsigned)time(NULL));
	directx->SetColorKey(false,0,0,0);

	game=new Game;
	if(game->Init(directx)==-1)return -1;
	directx->SetBeginTime();
	return 0;
}
