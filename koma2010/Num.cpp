#include "dx8.h"
#include "num.h"
#include "num_data.h"

Equation::Equation(){
}

Equation::~Equation(){
}

int Equation::Init(CDirectX* sdx){
	dx=sdx;
	img_num=dx->LoadGraph("img/img_num.bmp");
	img_mark=dx->LoadGraph("img/img_mark.bmp");
	return 0;
}

int Equation::Draw(){
/*	string ss="";
	char temp[256];
	for(int i=0;i<eq.size();i++){
		if(eq[i].type==0){
			sprintf(temp,"%d",eq[i].num);
			ss+=temp;
		}else{
			switch(eq[i].num){
			case 0:
				ss+="+";
				break;
			case 1:
				ss+="-";
				break;
			case 2:
				ss+="*";
				break;
			case 3:
				ss+="/";
				break;
			}
		}
	}
	pair<int,int> rs = Read();
	sprintf(temp," = %d/%d = %f",rs.first,rs.second,(float)rs.first/rs.second);
	ss+=temp;
	SetWindowText(GetWindowHandle(),ss.c_str());
	*/
	int x;
	for(x=0;x<eq.size();x++){
		switch(eq[x].type){
		case 0:
			dx->DrawGraph(IMG_NUM_ST_X+x*IMG_NUM_X,IMG_NUM_ST_Y,IMG_NUM_X,IMG_NUM_Y,IMG_NUM_ST_X+x*IMG_NUM_X,0,IMG_NUM_X,IMG_NUM_Y,img_num);
			break;
		case 1:
			dx->DrawGraph(IMG_NUM_ST_X+x*IMG_NUM_X,IMG_NUM_ST_Y,IMG_NUM_X,IMG_NUM_Y,IMG_NUM_ST_X+x*IMG_NUM_X,0,IMG_NUM_X,IMG_NUM_Y,img_mark);
			break;
		}
	}
	return 0;
}

int Equation::Proc(){
	return 0;
}

int Equation::Add(int type,int num){
	bool check;
	if(eq.size()==0){
		check=(type==0);
	}else{
		check= (eq[eq.size()-1].type!=type);
	}
	
	if(check){
		NumMark nm;
		nm.num=num;
		nm.type=type;
		eq.push_back(nm);
	}
	return 0;
}

pair<int,int> Equation::Read(){
	if(eq.size()==0) return make_pair(0,1);

	if(eq[eq.size()-1].type==1)return make_pair(0,1);

	vector < pair<int,int> > r;
	int x;
	for(x=0;x<eq.size();x++){
		r.push_back(make_pair(eq[x].num,1));
	}
	while(r.size()>2){
		int op=r[1].first;
		if(op==0){
			r[0].first=r[0].first*r[2].second+r[2].first*r[0].second;
			r[0].second=r[0].second*r[2].second;
		}else if(op==1){
			r[0].first=r[0].first*r[2].second-r[2].first*r[0].second;
			r[0].second=r[0].second*r[2].second;
		}else if(op==2){
			r[0].first=r[0].first*r[2].first;
			r[0].second=r[0].second*r[2].second;
		}else if(op==3){
			r[0].first=r[0].first*r[2].second;
			r[0].second=r[0].second*r[2].first;
		}
		r.erase(r.begin()+1);
		r.erase(r.begin()+1);
		r.swap(r);
		int g=gcd(r[0].first,r[0].second);
		r[0].first/=g;
		r[0].second/=g;
	}
	return r[0];
}