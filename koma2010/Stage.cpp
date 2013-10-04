#include "stage.h"
#include "map_data.h"

int Stage::Load(int num){
	FILE *fp;
	char stdir[256];
	int x,y;
	for(y=0;y<MapY;y++){
		for(x=0;x<MapX;x++){
			block[y][x]=0;
		}
	}
	sprintf(stdir,"stage/%d.map",num);
	fp=fopen(stdir,"r");
	if(fp!=NULL){
		for(y=0;y<MapY;y++){
			char col[256];
			fgets(col,256,fp);
			
			for(x=0;x< MapX ;x++){
				if(strlen(col)<=x){
					block[y][x]=0;
				}else{
					if('0'<=col[x] && col[x]<='9')
						block[y][x]=col[x]-'0';
					else if('a'<=col[x] && col[x]<='z')
						block[y][x]=col[x]-'a'+10;
					else
						block[y][x]=0;
				}
			}
		}
		fclose(fp);
	}
	else{
		char mes[512];
		sprintf("mes","%s not found.",stdir);
		char n[256];
		GetGameName(n);
		MessageBox(GetWindowHandle(),n,mes,MB_OK);
	}

	sprintf(stdir,"stage/%d.arr",num);
	fp=fopen(stdir,"r");
	if(fp!=NULL){
		fscanf(fp,"%d",&rest);
		fscanf(fp,"%d %d %d",&(player.x),&(player.y),&(player.k));
		fscanf(fp,"%d %d %d",&(goal.x),&(goal.y),&(goal.k));

		fclose(fp);
	}
	else{
		char mes[512];
		sprintf("mes","%s not found.",stdir);
		char n[256];
		GetGameName(n);
		MessageBox(GetWindowHandle(),n,mes,MB_OK);
	}
	
	return 0;
}

int Stage::Reset(){
	return 0;
}