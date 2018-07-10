#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#ifdef AKARI
    void c_() { std::cerr << "\033[39;0m" << std::endl; }
    template<typename T, typename... Args>
    void c_(T a, Args... args) { std::cerr << a << ", "; c_(args...); }
    #define ccc(args...) std::cerr << "\033[32;1m" << #args << "  =  ", c_(args)
    #define ccd(args...) std::cerr << "\033[32;1m", c_(args)
    #define ccf(args...) fprintf(stderr, args)
    #define crep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#else
    #define ccc(...) 0
    #define ccd(...) 0
    #define ccf(...) 0
    #define crep(...) if (false)
#endif
typedef long long ll;
typedef const int cint;
typedef const long long cll;
typedef const char cchar;
#define oper operator
#define daze << '\n'
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[20],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}char*gs(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return x+1;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p;*this>>p;if(c=='.'){int y=0,k=0;for(c=gc();isdigit(c);c=gc())y=y*10+(c-'0'),++k;x=(double)y/p_[k-1];if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 10> io;

cint N = 2003, mo = 998244353;
// a   c
// 
// b   d
int chk(cint x) {
    return x >= mo ? x - mo : x;
}
int chk2(cint x) {
    return x < 0 ? x + mo : x;
}
int qpow(ll a, int n) {
    ll res = 1;
    for (; n; n >>= 1, a = a * a % mo)
        if (n & 1)
            res = res * a % mo;
    return res;
}
int n, m, k, ups[N][N], dns[N][N];
ll ta[N][N], tb[N][N], tc[N][N], td[N][N], ts[N][N];
int calc(cint _, cint __) {
    int res = 0;
    rep (i, 1, n) {
        ll *f = ts[i], *g = ts[i - 1], *a = ta[i], *b = tb[i + _], *c = tc[i] + __, *d = td[i + _] + __;
        rep (j, 1, m) {
            f[j] = g[j] + f[j - 1] - g[j - 1] + a[j] + b[j] + c[j] + d[j];
            res = chk(res + qpow(f[j] % mo, k));
        }
    }
    return res;
}
char ch[N][N];
int main() {
    io >> n >> m >> k;
    rep (i, 1, n)
        io >> ch[i] + 1;
    rep (i, 1, n) {
        int *f = ups[i], *g = ups[i - 1];
        char *a = ch[i];
        rep (j, 1, m)
            f[j] = a[j] == '1' ? g[j] + 1 : 0;
    }
    per (i, n, 1) {
        int *f = dns[i], *g = dns[i + 1];
        char *a = ch[i];
        rep (j, 1, m)
            f[j] = a[j] == '1' ? g[j] + 1 : 0;
    }
    rep (i, 1, n) {
        static int q[N];
        int *up = ups[i], *dn = dns[i], *qr;
        ll *a = ta[i], *b = tb[i + 1], *c = tc[i] + 1, *d = td[i + 1] + 1;
        *(qr = q + 1) = m + 1;
        ll res = 0;
        per (j, m, 1) { // (i, j) as left-top corner
            for (; qr > q && dn[*qr] >= dn[j]; --qr)
                res -= (*(qr - 1) - *qr) * dn[*qr];
            res += (*qr - j) * dn[j];
            a[j] += res;
            *++qr = j;
        }
        *(qr = q + 1) = m + 1;
        res = 0;
        per (j, m, 1) { // (i, j) as left-bottom corner
            for (; qr > q && up[*qr] >= up[j]; --qr)
                res -= (*(qr - 1) - *qr) * up[*qr];
            res += (*qr - j) * up[j];
            b[j] -= res;
            *++qr = j;
        }
        *(qr = q + 1) = 0;
        res = 0;
        rep (j, 1, m) { // (i, j) as right-top corner
            for (; qr > q && dn[*qr] >= dn[j]; --qr)
                res -= (*qr - *(qr - 1)) * dn[*qr];
            res += (j - *qr) * dn[j];
            c[j] -= res;
            *++qr = j;
        }
        *(qr = q + 1) = 0;
        res = 0;
        rep (j, 1, m) { // (i, j) as right-bottom corner
            for (; qr > q && up[*qr] >= up[j]; --qr)
                res -= (*qr - *(qr - 1)) * up[*qr];
            res += (j - *qr) * up[j];
            d[j] += res;
            *++qr = j;
        }
    }
    io << chk2(chk(calc(0, 0) + calc(1, 1)) - chk(calc(0, 1) + calc(1, 0))) daze;
}
