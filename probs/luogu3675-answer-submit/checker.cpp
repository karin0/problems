#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
#include "testlib.h"
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define VIZ {printf("digraph G{\n"); for(int i=1;i<=n;i++) for es(i,e) printf("%d->%d;\n",i,vb[e]); puts("}");}
#define VIZ2 {printf("graph G{\n"); for(int i=1;i<=n;i++) for es(i,e) if(vb[e]>=i)printf("%d--%d;\n",i,vb[e]); puts("}");}
#define SZ 666666
int _,n,v[SZ];
ld t,s,k1,k2,x[SZ],y[SZ],r[SZ];
bool del[SZ];
#define sqr_(x) ((x)*(x))
#define ii inf.readInt()
#define id inf.readDouble()
int main(int argc,char** argv)
{
    setName("mine checker");
    registerTestlibCmd(argc,argv);
    s=id,t=id,k1=id,k2=id,n=ii;
    ld cp=s,pi=acos(-1),eps=1e-7;
    for(int i=1;i<=n;i++)
    {
    x[i]=id,y[i]=id,r[i]=id,v[i]=ii;
    if(r[i]<=eps) quitf(_fail,"bad input: r[%d] too small",i);
    if(0<=y[i]-r[i]&&y[i]+r[i]<=s&&0<=x[i]-r[i]&&x[i]+r[i]<=s+s);
    else quitf(_fail,"bad input: circle %d out of range",i);
	}
    for(int i=1;i<=n;i++)
    {
    for(int j=i+1;j<=n;j++)
    {
    	if(sqr_(x[i]-x[j])+sqr_(y[i]-y[j])<=r[i]*r[i])
		quitf(_fail,"bad input: circle %d and %d intersect",i,j);
	}
	}
    int h=0; ll tv=0; ld t_=t;
    while(!ouf.seekEof())
    {
    	++h;
    	if(h>2*n) {--h; break;}
    	string S=ouf.readToken();
    	if(S!="m"&&S!="g")
		quitf(_wa,"operation not m or g");
		ld g;
		if(S=="m") g=ouf.readDouble(0,s+s,"move_position");
		else g=ouf.readDouble(0.2,179.8,"grab_angle");
		if(S=="m")
		{
			t-=fabs(cp-g)*k1;
			if(t<-eps) {--h; break;} //tle
			cp=g; continue;
		}
		g=g/180*pi;
		//x=ky+b ¹ý(cp,0)
		ld k=tan(pi/2-g),b=cp,md=1e18;int p=-1;
		for(int j=1;j<=n;j++)
		{
			if(del[j]) continue;
			//(ky+b-x[j])^2+(y-y[j])^2=r[j]^2
			//(k^2+1)y+(2k(b-x[j])-2y[j])y
			//+(b-x[j])^2+y[j]^2-r[j]^2=0
			ld A=1+k*k,
			B=-2*y[j]+2*k*(b-x[j]),
			C=y[j]*y[j]-r[j]*r[j]+(b-x[j])*(b-x[j]),
			D=B*B-4*A*C;
			if(D<0) continue;
			ld y1=(-B+sqrt(D))/(2*A),
			y2=(-B-sqrt(D))/(2*A),
			x1=y1*k+b,x2=y2*k+b,
			d1=sqrt((x1-cp)*(x1-cp)+y1*y1),
			d2=sqrt((x2-cp)*(x2-cp)+y2*y2),
			dis=min(d1,d2);
			if(fabs(d1-d2)<eps) continue;
			if(dis<md) md=dis,p=j;
		}
		if(p==-1) continue;
		t-=md*k2;
		if(t<-eps) {--h; break;} //tle
		del[p]=1; tv+=v[p];
	}
	while(!ouf.seekEof()) ouf.readToken();
	ll b=ans.readInt();
	ld w=ans.readReal();
	int f=ans.readInt(0,1);
	if(b<tv)
		quitp(1+0.1*f,"Your ans %lld is better than std! done %d attempts, \
time used %.4lf, %.4lf remained",tv,h,t_-t,t);
	else if(b<0)
		quitf(_wa,"Your answer %lld <0, done %d attempts, \
time used %.4lf, %.4lf remained",tv,h,t_-t,t);
	else
	{
		ld scr=floor(pow((ld)tv/b,w)*10);
		quitp(scr*0.1,"Your ans is %lld, done %d attempts, \
time used %.4lf, %.4lf remained",tv,h,t_-t,t);
	}
}

