#include "function.h"
#include "dx8.h"

class b2MyListener : public b2ContactListener{
private:
	CDirectX* dx;
	int wav_crash1;
	int wav_crash2;
	int wav_coin;
	b2Body* pl;
	b2Body* gl;
	int* coin;
public:
	virtual int Init(CDirectX*);
	virtual void BeginContact(b2Contact*);
	virtual void EndContact(b2Contact*);
	void Set(b2Body* player,b2Body* goal,int* c){
		pl=player;
		gl=goal;
		coin=c;
	}
};