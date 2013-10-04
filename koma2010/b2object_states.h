class b2State{
public:
	int type;
	int kind;
	int gflag;
	b2State(){
		type=-1;
		kind=-1;
		gflag=0;
	}
	b2State(int skind,int stype){
		type=stype;
		kind=skind;
		gflag=0;
	}
	void Set(int skind,int stype){
		type=stype;
		kind=skind;
		gflag=0;
	}
};