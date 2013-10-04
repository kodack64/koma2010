#include "map.h"
#include "map_data.h"
#include "box2d_data.h"
#include "var.h"

Map::Map(){};

Map::~Map(){
	int x,y;
	for(y=0;y<MapY;y++){
		for(x=0;x<MapX;x++){
			SAFE_DELETE(bstate[y][x]);
		}
	}
}

int Map::Main(){
	return 0;
}

int Map::Init(CDirectX *cdx,Mouse* m,Key* k){
	dx=cdx;
	mouse=m;
	key=k;
	int x,y;
	for(y=0;y<MapY;y++){
		for(x=0;x<MapX;x++){
			bstate[y][x] = new b2State(1,0);
			bbody[y][x]=NULL;
			block[y][x]=0;
		}
	}

	Load();
	return 0;
}

int Map::Load(){
	dx->SetColorKey(true,0,255,0);
	img_block=dx->LoadGraph("img/block.bmp");
	img_goal=dx->LoadGraph("img/goal.bmp");
	img_coin=dx->LoadGraph("img/coin.bmp");
	return 0;
}

int Map::Set(int bl[][MapX]){
	int x,y;
	b2Vec2 tri[3];
	b2Vec2 four[4];
	b2Vec2 penta[5];
	float rdump = 0.5f;
	float ldump = 0.5f;
	float density = 1.0f;
	float fric = 0.3f;
	float rest = 0.5f;
	float heavy = 5.0f;
	float boundy = 0.8f;
	for(y=0;y<MapY;y++){
		for(x=0;x<MapX;x++){
			b2Body* temp=NULL;
			bstate[y][x]->Set(1,bl[y][x]);
			block[y][x]=bl[y][x];
			switch(bl[y][x]){
			case 1:	//static box
				temp = dx->b2CreateBox(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,BlockY/2,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 2: //dynamic box
				temp = dx->b2CreateBox(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,BlockY/2,rdump,ldump,density,fric,rest,true,false,bstate[y][x]);
				break;
			case 3: //static rightup triangle 
				tri[0].Set(BlockX/2,-BlockY/2);
				tri[1].Set(BlockX/2,BlockY/2);
				tri[2].Set(-BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,tri,3,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 4: //static leftup triangle
				tri[0].Set(-BlockX/2,-BlockY/2);
				tri[1].Set(BlockX/2,BlockY/2);
				tri[2].Set(-BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,tri,3,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 5: //static rightup triangle1
				tri[0].Set(BlockX/2,-BlockY/4);
				tri[1].Set(BlockX/2,BlockY/2);
				tri[2].Set(-BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,tri,3,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 6: //static rightup triangle2
				four[0].Set(-BlockX/2,0);
				four[1].Set(BlockX/2,-BlockY/2);
				four[2].Set(BlockX/2,BlockY/2);
				four[3].Set(-BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,four,4,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 7: //static leftup triangle2
				tri[0].Set(-BlockX/2,-BlockY/4);
				tri[1].Set(BlockX/2,BlockY/2);
				tri[2].Set(-BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,tri,3,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 8: //static leftup triangle2
				four[0].Set(-BlockX/2,-BlockY/2);
				four[1].Set(BlockX/2,0);
				four[2].Set(BlockX/2,BlockY/2);
				four[3].Set(-BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,four,4,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 9: //static circle
				temp = dx->b2CreateCircle(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 10: //dynamic circle
				temp = dx->b2CreateCircle(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,rdump,ldump,density,fric,rest,true,false,bstate[y][x]);
				break;
			case 11: //big static box
				temp = dx->b2CreateBox(x*BlockX+BlockX,y*BlockY+BlockY,BlockX,BlockY,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 12: //big dynamic box
				temp = dx->b2CreateBox(x*BlockX+BlockX,y*BlockY+BlockY,BlockX,BlockY,rdump,ldump,density,fric,rest,true,false,bstate[y][x]);
				break;
			case 13: //big static Circle
				temp = dx->b2CreateCircle(x*BlockX+BlockX,y*BlockY+BlockY,BlockX,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 14: //big dynamic Circle
				temp = dx->b2CreateCircle(x*BlockX+BlockX,y*BlockY+BlockY,BlockX,rdump,ldump,density,fric,rest,true,false,bstate[y][x]);
				break;
			case 15: //heavy dynamic box
				temp = dx->b2CreateBox(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,BlockY/2,rdump,ldump,heavy,fric,rest,true,false,bstate[y][x]);
				break;
			case 16: //heavy dynamic circle
				temp = dx->b2CreateCircle(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,rdump,ldump,heavy,fric,rest,true,false,bstate[y][x]);
				break;
			case 17:// boundy static box
				temp = dx->b2CreateBox(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,BlockY/2,rdump,ldump,density,fric,boundy,false,false,bstate[y][x]);
				break;
			case 18: //boundy dynamic box
				temp = dx->b2CreateBox(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,BlockY/2,rdump,ldump,density,fric,boundy,true,false,bstate[y][x]);
				break;
			case 19: //static rightup triangle 
				tri[0].Set(-BlockX/2,-BlockY/2);
				tri[1].Set(BlockX/2,-BlockY/2);
				tri[2].Set(BlockX/2,BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,tri,3,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 20: //static leftup triangle
				tri[0].Set(BlockX/2,-BlockY/2);
				tri[1].Set(-BlockX/2,BlockY/2);
				tri[2].Set(-BlockX/2,-BlockY/2);
				temp = dx->b2CreatePolygon(x*BlockX+BlockX/2,y*BlockY+BlockY/2,tri,3,rdump,ldump,density,fric,rest,false,false,bstate[y][x]);
				break;
			case 33: //coin
				bstate[y][x]->kind=3;
				bstate[y][x]->type=0;
				temp = dx->b2CreateCircle(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,rdump,ldump,density,fric,rest,false,true,bstate[y][x]);
				break;
			case 34: //power
				bstate[y][x]->kind=4;
				bstate[y][x]->type=0;
				temp = dx->b2CreateCircle(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,rdump,ldump,density,fric,rest,false,true,bstate[y][x]);
				break;
			case 35: //goal
				bstate[y][x]->kind=2;
				bstate[y][x]->type=0;
				temp = dx->b2CreateBox(x*BlockX+BlockX/2,y*BlockY+BlockY/2,BlockX/2,BlockY/2,rdump,ldump,density,fric,rest,false,true,bstate[y][x]);
				break;
			}
			bbody[y][x]=temp;
		}
	}
	return 0;
}
int Map::DrawTile(){
	int x,y;
	b2Vec2 v;
	for(y=0;y<480/BlockX;y++){
		for(x=0;x<640/BlockY;x++){
			v.x=BlockX*x+BlockX/2;
			v.y=BlockY*y+BlockY/2;
			dx->DrawGraph(v.x-BlockX/2,v.y-BlockY/2,BlockX,BlockY,0,0,IMG_BlockX,IMG_BlockY,0,1.0f,img_block);
		}
	}
	return 0;
}
int Map::Draw(){
	int x,y;
	b2Vec2 v;
	for(y=0;y<MapY;y++){
		for(x=0;x<MapX;x++){
			switch(block[y][x]){
			case -1:
				break;
			default:
				v.x=BlockX*x+BlockX/2;
				v.y=BlockY*y+BlockY/2;
				dx->DrawGraph((v.x-BlockX/2)*perc,(v.y-BlockY/2)*perc,BlockX,BlockY,0,0,IMG_BlockX,IMG_BlockY,0,1.0f*perc,img_block);
				break;
			}
		}
	}
	for(y=0;y<MapY;y++){
		for(x=0;x<MapX;x++){
			switch(block[y][x]){
			case 0:
				break;
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				v = bbody[y][x]->GetPosition();
				v.x=v.x*MtoPIX;
				v.y=v.y*MtoPIX;
				dx->DrawGraph((v.x-BlockX/2)*perc,(v.y-BlockY/2)*perc,BlockX,BlockY,IMG_BlockX*block[y][x],0,IMG_BlockX,IMG_BlockY,(bbody[y][x]->GetAngle()*360/2/PI),1.0f*perc,img_block);
				break;
			case 11:
			case 12:
			case 13:
			case 14:
				v = bbody[y][x]->GetPosition();
				v.x=v.x*MtoPIX;
				v.y=v.y*MtoPIX;
				dx->DrawGraph((v.x-BlockX)*perc,(v.y-BlockY)*perc,BlockX*2,BlockY*2,IMG_BlockX*block[y][x],0,IMG_BlockX,IMG_BlockY,(bbody[y][x]->GetAngle()*360/2/PI),1.0f*perc,img_block);
				break;
			case 33:
				if(((b2State*)(bbody[y][x]->GetUserData()))->gflag==0){
					v = bbody[y][x]->GetPosition();
					v.x=v.x*MtoPIX;
					v.y=v.y*MtoPIX;
					dx->DrawGraph((v.x-BlockX/2)*perc,(v.y-BlockY/2)*perc,BlockX,BlockY,0,0,IMG_BlockX,IMG_BlockY,(bbody[y][x]->GetAngle()*360/2/PI),1.0f*perc,img_coin);
				}
				break;
			case 34:
				break;
			case 35:
				v = bbody[y][x]->GetPosition();
				v.x=v.x*MtoPIX;
				v.y=v.y*MtoPIX;
				dx->DrawGraph((v.x-BlockX/2)*perc,(v.y-BlockY/2)*perc,BlockX,BlockY,0,0,IMG_BlockX,IMG_BlockY,(bbody[y][x]->GetAngle()*360/2/PI),1.0f*perc,img_goal);
				break;
			case -1:
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

int Map::GetKind(int x,int y){
	return block[y/BlockY][x/BlockX];
}
int Map::CanGo(int k){
	return k==0;
}
