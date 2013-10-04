#include "dx8.h"


class NumMark{
public:
	NumMark(){
	};
	~NumMark(){
	};

public:
	int type;
	int num;
	string toString(){
		string s;
		if(type==0){
			char temp[256];
			sprintf(temp,"%d",num);
			s=temp;
		}
		else{
			switch(num){
			case 0:
				return "+";
				break;
			case 1:
				return "-";
				break;
			case 2:
				return "*";
				break;
			case 3:
				return "/";
				break;
			default:
				return "";
				break;
			}
		}
	}
};

class Equation{
private:
	CDirectX* dx;
	int img_num;
	int img_mark;
public:
	Equation();
	virtual ~Equation();
	vector <NumMark> eq;

	int gcd(int m, int n)
	{
		int r;
		if (m < n) {
			swap(m, n);
		}
		if (n == 0) {
			return m;
		}
		if ((r = m % n)) {
			return gcd(n, r);
		}
		return n;
	}

	int lcm(int m, int n)
	{
		return (m * n) / gcd(m, n);
	}
	virtual int Proc();
	virtual int Draw();
	virtual int Init(CDirectX*);
	virtual int Add(int type,int num);
	virtual pair<int,int> Read();
};