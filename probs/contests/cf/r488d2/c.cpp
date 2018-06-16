#include <bits/stdc++.h>
#define rep(__i,__s,__t) for((__i)=(__s);(__i)<=(__t);++(__i))
#define re(__i,__s,__t) for((__i)=(__s);(__i)<(__t);++(__i))
#define per(__i,__s,__t) for((__i)=(__s);(__i)>=(__t);--(__i))
#define pe(__i,__s,__t) for((__i)=(__s);(__i)>(__t);--(__i))
#ifdef AKARI
    #define ccc(x) std::cerr << #x " = " << (x) << "  "
    #define ccf(x) std::cerr << #x " = " << (x) << std::endl
    #define cccc(...) fprintf(stderr, __VA_ARGS__)
#else
    #define ccc(x)
    #define ccf(x)
    #define cccc(...)
#endif
struct IO{static const int L=1000000;char a[L],b[L],*s,*t,*p,c;IO():p(b){}~IO(){fwrite(b,1,p-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,L,stdin);return*s++;}void gs(char*st){for(c=gc();!isgraph(c);c=gc());*st++=c;for(c=gc();isgraph(c);c=gc())*st++=c;*st++=0;}template<class T>operator T(){static T x;static bool neg;for(c=gc();c!='-'&&!isdigit(c);c=gc());if((neg=c=='-'))c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');return neg?-x:x;}void pc(const char ch){if(p==b+L)fwrite(p=b,1,L,stdout);*p++=ch;}template<class T>void print(T x,const char end='\n'){static char cs[30],*q;static T y;if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;for(q=cs;x;x=y)y=x/10,*q++=x-y*10+'0';while(q!=cs)pc(*--q);}if(end)pc(end);}void ps(const char*st,const char end='\n'){while(*st)pc(*st++);if(end)pc(end);}}io;
typedef long long ll;

struct point {
    int x, y;
    point() {}
    point(int _x, int _y) : x(_x), y(_y) {}
    point(point a, point b) : x(b.x-a.x), y(b.y-a.y) {}
    int operator ^ (const point &rh) const {
        return x * rh.y - y * rh.x;
    }
} va[7], vb[7];
struct line {
    point a, b;
    line() {}
    line(point _a, point _b) : a(_a), b(_b){}
} pa[7], pb[7];
int mult(point a, point b, point c)  
{  
    return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);  
}  
  
using std::max;
using std::min;
bool on(point &p, line &l) {
    return (point(l.a, p) ^ point(p, l.b)) == 0 && (l.a.x - p.x) * (p.x - l.b.x) >= 0 && (l.a.y - p.y) * (p.y - l.b.y) >= 0;
}
bool crs(line a, line b)  {  
    if (on(a.a, b) || on(a.b, b) || on(b.a, a) || on(b.b, a))
        return true;
    point aa = a.a, bb = a.b, cc = b.a, dd = b.b;
    if ( max(aa.x, bb.x)<min(cc.x, dd.x) )  
    {  
        return false;  
    }  
    if ( max(aa.y, bb.y)<min(cc.y, dd.y) )  
    {  
        return false;  
    }  
    if ( max(cc.x, dd.x)<min(aa.x, bb.x) )  
    {  
        return false;  
    }  
    if ( max(cc.y, dd.y)<min(aa.y, bb.y) )  
    {  
        return false;  
    }  
    if ( mult(cc, bb, aa)*mult(bb, dd, aa)<0 )  
    {  
        return false;  
    }  
    if ( mult(aa, dd, cc)*mult(dd, bb, cc)<0 )  
    {  
        return false;  
    }  
    return true;  
}  
int mul(point p1, point p2, point p3)  
{  
    return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);  
}  
  
bool ine(line a, line b)  
{  
    if (on(a.a, b) || on(a.b, b) || on(b.a, a) || on(b.b, a))
        return true;
    point p1 = a.a, p2 = a.b, q1 = b.a, q2 = b.b;
    if(max(p1.x,p2.x)<min(q1.x,q2.x)||max(q1.x,q2.x)<min(p1.x,p2.x)||max(p1.y,p2.y)<min(q1.y,q2.y)||max(q1.y,q2.y)<min(p1.y,p2.y))  
        return 0;  
    if(mul(p1,p2,q1)*mul(p1,p2,q2) <= 0 && mul(q1,q2,p1)*mul(q1,q2,p2) <= 0)  
        return 1;  
    return 0;  
}  
  
bool in(point &a, line *pl) {
    int i, cnt = 0;
    rep (i, 1, 4) {
        line &lin = pl[i];
        if (on(a, lin))
            return true;
        if (ine(lin, line(a, point(300, a.y))))
            ++cnt;
        // if (lin.a.y <= a.y && a.y <= lin.b.y && (point(a, lin.a) ^ point(a, lin.b)) < 0)
        //    ++cnt;
    }
    return cnt & 1;
}
bool pin(point *pva, line *plb) {
    int i;
    rep (i, 1, 4)
        if (!in(pva[i], plb))
            return false;
    return true;
}
int main() {
    static int i, j;
    rep (i, 1, 4) {
        va[i].x = io;
        va[i].y = io;
    }
    rep (i, 1, 3)
        pa[i].a = va[i], pa[i].b = va[i + 1];
    pa[4].a = va[4], pa[4].b = va[1];
    rep (i, 1, 4) {
        vb[i].x = io;
        vb[i].y = io;
    }
    rep (i, 1, 3)
        pb[i].a = vb[i], pb[i].b = vb[i + 1];
    pb[4].a = vb[4], pb[4].b = vb[1];
    if (pin(va, pb) || pin(vb, pa))
        return puts("YES");
    rep (i, 1, 4) rep (j, 1, 4) if (ine(pa[i], pb[j]))
        return puts("YES");
    puts("NO");
    return 0;
}

