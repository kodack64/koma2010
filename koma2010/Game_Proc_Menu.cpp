#include "game.h"

int Game::ProcMenu(){
	switch(menu->Main()){
	case 0:
		//menu
		break;
	case 1:
		//start
		gs=ST_TAP;
		tap->Reset();
		break;
	case 2:
		gs=ST_END;
		//tutorial
		break;
	case 3:
		//replay
		break;
	case 4:
		//exit
		gs=ST_END;
		break;
	default:
		break;
	}
	return 0;
}