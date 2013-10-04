#include "tap.h"
#include "map_data.h"

int Tap::ProcResult(){
	dx->DeleteDuplicatedWav();
	if(stagecount<MaxStage){
		ts=ST_TAP_LOAD;
		stagecount++;
	}
	else{
		if(!regist){
			splash->Set(2,&stagecount,&coin,&score,&shot,&rest,&totalscore,player->GoalCheck());
			RegistScore();
			regist=true;
		}
		if(splash->Proc()==1){
			return 1;
		}
	}
	return 0;
}

int Tap::RegistScore(){
	FILE* fp;
	fp=fopen("dat/score.txt","r");
	if(fp!=NULL){
		vector <int> scorelist;
		int scan;
		while(~fscanf(fp,"%d",&scan)){
			scorelist.push_back(scan);
		}
		fclose(fp);
		sort(scorelist.rbegin(),scorelist.rend());
		int i,ra;
		bool ch=true;
		for(i=0;i<scorelist.size();i++){
			if(totalscore>scorelist[i]){
				scorelist.insert(scorelist.begin()+i,totalscore);
				ra=i+1;
				ch=false;
				break;
			}
		}
		if(ch){
			scorelist.push_back(totalscore);
			ra=scorelist.size();
		}
		fp=fopen("dat/score.txt","w");
		for(i=0;i<scorelist.size();i++){
			fprintf(fp,"%d\n",scorelist[i]);
		}

		rank=ra;
		playnum=scorelist.size();
		topscore=scorelist[0];
	}else{
		fp=fopen("dat/score.txt","w");
		fprintf(fp,"%d\n",totalscore);
		fclose(fp);
		rank=1;
		playnum=1;
		topscore=0;
	}
	splash->Set2(&rank,&topscore,&playnum);
	return 0;
}