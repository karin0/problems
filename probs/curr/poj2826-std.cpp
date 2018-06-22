#include<cstdio>
#include<iostream>
#include<algorithm>
#include<ctime>
#include<cstring>
#include<string>
#include<queue>
#include<cmath>

#define file(f) freopen(f".in","r",stdin); freopen(f".out","w",stdout)

#define min(a,b) ((a)<(b)? (a):(b))
#define max(a,b) ((a)>(b)? (a):(b))

using namespace std;

const double EPS = 1e-8;
const double INF = 10000 + 10;

int dcmp(double a){
    if(fabs(a) < EPS) return 0;
    else return a < 0 ? -1 : 1;
}

struct R{
    double dat;
    void r(){
        scanf("%lf",&dat);
    }
    void w(){
        printf("%.2lf\n",dat);
    }
    bool operator == (const R c){
        return !dcmp(dat - c.dat);//dat-EPS < c.dat && dat+EPS > c.dat;
    }
    bool operator < (const R c){
        return dcmp(dat - c.dat) == -1;
    }
    bool operator > (const R c){
        return dcmp(dat - c.dat) == 1;
    }
    bool operator >= (const R c){
        return (*this).operator==(c) || (*this).operator>(c);
    }
    bool operator <= (const R c){
        return (*this).operator==(c) || (*this).operator<(c);
    }
    R operator + (const R c){
        R a;
        a.dat = dat + c.dat;
        return a;
    }
    R operator - (const R c){
        R a;
        a.dat = dat - c.dat;
        return a;
    }
    R operator * (const R c) const{
        R a;
        a.dat = dat * c.dat;
        return a;
    }
    R operator / (const R c){
        R a;
        a.dat = dat / c.dat;
        return a;
    }
};
R zero,two,minu;//zero == (double)0,two == (double)2,minu == (double)-1;

struct P{
    R x,y;
    void r(){
        x.r(),y.r();
    }
    P operator - (const P c){
        P a;
        a.x = x - c.x,a.y = y - c.y;
        return a;
    }
    P operator + (const P c){
        P a;
        a.x = x + c.x,a.y = y + c.y;
        return a;
    }
    P operator * (const R c){
        P a;
        a.x = x * c,a.y = y * c;
        return a;
    }
    P operator / (const R c){
        P a;
        a.x = x / c,a.y = y / c;
        return a;
    }
    bool operator < (const P c){
        return mo() < c.mo();
    }
    bool operator > (const P c){
        return mo() > c.mo();
    }
    R CP(P c){
        return (x*c.y) - (y*c.x);
    }
    R DP(P c){
        return (x*c.x) + (y*c.y);
    }
    R mo() const{
        R ret;
        ret.dat = sqrt((x.dat * x.dat) + (y.dat * y.dat));
        return ret;
    }
};

struct L{
    P f,t;//from,to
    R k;
    bool p;
    void getk(){
        P v = f+t;
        if(t.mo() == zero) k = zero;
        else if(v.x == f.x){
            p = 1;
            k.dat = INF;
        }
        else{
            p = 0;
            k = (v.y-f.y) / (v.x-f.x);
        }
    }
    void r(){
        P to;
        f.r(),to.r();
        if(to.y < f.y) swap(f,to);
        t = to - f;
        getk();
    }
    bool cr(L c){//判交
        P A1 = f,A2 = f + t,B1 = c.f,B2 = c.f + c.t;
        if(!(min(A1.x,A2.x) <= max(B1.x,B2.x) &&
             min(B1.x,B2.x) <= max(A1.x,A2.x) &&
             min(A1.y,A2.y) <= max(B1.y,B2.y) &&
             min(B1.y,B2.y) <= max(A1.y,A2.y) ))//快速排斥实验
            return false;
        if((A1-B1).CP(A2-B1) * (A1-B2).CP(A2-B2) > zero ||
           (B1-A1).CP(B2-A1) * (B1-A2).CP(B2-A2) > zero)//跨立实验
            return false;
        else
            return true;
    }
    P node(L c){//求交点
        P A1 = f,A2 = f + t,B1 = c.f,B2 = c.f + c.t;
        R p = (B1-A1).CP(B2-A1) / ((A1-B2).CP(A2-B2) - (A1-B1).CP(A2-B1));
        return (t * p) + f;
    }
};
L X,Y;

void init(L &l1,L &l2);
void work(L l1,L l2);
R work2(L l1,L l2);
R work3(L l1,L l2);

int main(){
#ifndef ONLINE_JUDGE
    file("2826");
#endif
    L l1,l2;
    int T;
    scanf("%d",&T);
    while(T --){
        init(l1,l2);
        work(l1,l2);
    }
    return 0;
}

void init(L &l1,L &l2){
    l1.r();
    l2.r();
    zero.dat = 0.00;
    two.dat = 2.00;
    minu.dat = -1.00;
    Y.t.y.dat = INF,Y.t.x.dat = 0;
}

void work(L l1,L l2){
    R ans;
    if(l1.k == zero || l2.k == zero || (!l1.cr(l2)))//有一条线段平行于x轴或互不相交
        ans = zero;
    else if(l1.p || l2.p)//有一条线段平行于y轴(已经排除了平行和不相交)
        ans = work2(l1,l2);
    else//还剩三种一般情况：同时左(右)斜或一左一右
        ans = work3(l1,l2);
    ans.w();
}

R work2(L l1,L l2){
    if(l2.p) swap(l1,l2);//l1为平行于y轴的线段
    P N = l1.node(l2),v1,v2;
    v1 = l2.f + l2.t - N;
    v2 = l1.f + l1.t - N;
    if(v1.mo() == zero || v2.mo() == zero) return zero;
    R cos = v1.DP(v2) / (v1.mo() * v2.mo());
    P h = (Y.t / Y.t.mo()) * min((v1 * cos).mo(),v2.mo());
    v1 = (v1/v1.mo()) * (h / cos).mo(),v2 = h;
    return max(v1.CP(v2),v1.CP(v2) * minu) / two;
}

R work3(L l1,L l2){
    P N = l1.node(l2);
    if(abs(l1.k.dat) < abs(l2.k.dat)) swap(l1,l2);//l1相比l2的更靠近y轴
    P v1,v2;
    L l3 = Y;
    l3.f = N;
    v1 = l1.f + l1.t - N;
    v2 = l2.f + l2.t - N;
    if(v1.mo() == zero || v2.mo() == zero) return zero;
    R cos1,cos2;
    cos1 = v1.DP(l3.t) / (v1.mo() * l3.t.mo());
    cos2 = v2.DP(l3.t) / (v2.mo() * l3.t.mo());
    P h1,h2;
    h1 = (Y.t / Y.t.mo()) * (v1.mo() * cos1);
    h2 = (Y.t / Y.t.mo()) * (v2.mo() * cos2);
    if((v1-h1).mo() >= (v2-h2).mo() && l1.k * l2.k > zero) return zero;
    else{
        l1.t = (l1.t / l1.t.mo()) * min(v1.mo(),(v2.mo() * cos2) / cos1);
        l2.t = (l2.t / l2.t.mo()) * min(v2.mo(),(v1.mo() * cos1) / cos2);
        l3.t = (l3.t / l3.t.mo()) * l1.t.mo() * cos1;
        R r1 = l3.t.CP(l1.t) / two,r2 = l3.t.CP(l2.t) / two,ret;
        ret = r1 - r2;
        return max(ret,ret * minu);//即abs(ret)
    }
}
