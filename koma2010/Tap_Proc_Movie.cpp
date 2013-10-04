/*#include "tap.h"
#include "movie_data.h"

int Tap::MoviePlay(){
	ProcMovieKey();
	if(ms == MS_PLAY){		
		MovieNextFrame(1);
	}else if(ms==MS_STOP){
		if(key->GetKey(VK_RIGHT)){
			MovieNextFrame(1);
		}
		if(key->GetKey(VK_UP)){
			MovieNextFrame(MOVIE_FAST);
		}

		if(key->GetKey(VK_LEFT)){
			MovieLastFrame(1);
		}
		if(key->GetKey(VK_DOWN)){
			MovieLastFrame(MOVIE_FAST);
		}
	}

	if(key->GetKeyNow(VK_SPACE)){
		if(ms==MS_PLAY){
			ms=MS_STOP;
		}else{
			ms=MS_PLAY;
		}
	}
	return 0;
}

int Tap::MovieReset(){
	map->Set(stage->block);
	player->Set(stage->player.x,stage->player.y);
	player->BackReset();
	frame=0;
	memset(rb,false,sizeof(rb));
	return 0;
}
*/