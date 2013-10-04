#include "game.h"

int Game::ProcTap(){
	if(tap->Main()==1){
		gs=ST_RESULT;
	}
	return 0;
}