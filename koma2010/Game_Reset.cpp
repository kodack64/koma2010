#include "game.h"

int Game::Reset(){
	gs=ST_MENU;
	menu->Reset();
	/**/
//	gs=ST_TAP;
//	tap->Reset();
	/**/
	return 0;
}