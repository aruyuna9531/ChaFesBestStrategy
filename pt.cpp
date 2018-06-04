#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

#define ScoreRank 1.20
#define ComboRank 1.08
#define ArrangeBonus 1.15

int round(double x){
	int s=(int)x;
	if(x-(double)s>=0.5)return s+1;
	else return s;
}

int pts(int r){
	//每轮1倍pt
	return round((282+19*r)*ScoreRank*ComboRank*ArrangeBonus);
}

class b{
public:
	int r[5];
	int totalpt;
	int totalLP;
	double averagePt;
	b(int a1, int a2, int a3, int a4, int a5){
		r[0]=a1;
		r[1]=a2;
		r[2]=a3;
		r[3]=a4;
		r[4]=a5;
		totalpt=0;
		int i=0;
		for(i=0;i<5;i++)totalpt+=r[i]*pts(i+1);
		totalLP=0;
		for(i=0;i<5;i++)totalLP+=r[i]*25;
		averagePt=(double)totalpt/(double)totalLP;
	}
	b(const b &x){
		for(int i=0;i<5;i++)r[i]=x.r[i];
		totalpt=x.totalpt;
		totalLP=x.totalLP;
		averagePt=x.averagePt;
	}
	b& operator=(const b& x){
		for(int i=0;i<5;i++)r[i]=x.r[i];
		totalpt=x.totalpt;
		totalLP=x.totalLP;
		averagePt=x.averagePt;
		return *this;
	}
};

int main(){
	vector<b> v1;
	for(int r1=1;r1<5;r1++)for(int r2=r1;r2<5;r2++)for(int r3=r2;r3<5;r3++)for(int r4=r3;r4<5;r4++)for(int r5=r4;r5<5;r5++){
		b a(r1,r2,r3,r4,r5);
		v1.push_back(a);
	}
	for(int i=v1.size()-1;i>=0;i--){
		for(int j=0;j<i;j++){
			if(v1.at(j).averagePt>v1.at(j+1).averagePt){
				b tmp(v1.at(j));
				v1.at(j)=v1.at(j+1);
				v1.at(j+1)=tmp;
			}
		}
	}
	int rank=1;
	while(v1.empty()!=true){
		b *tmp=&v1[v1.size()-1];
		v1.pop_back();
		printf("排名：%d,倍数：%d,%d,%d,%d,%d,可获得pt:%d,消耗LP:%d,平均每LP获得pt:%f\n",rank++,tmp->r[0],tmp->r[1],tmp->r[2],tmp->r[3],tmp->r[4],tmp->totalpt,tmp->totalLP,tmp->averagePt);
	}
	return 0;
}
