#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define go(e_,s_) for(Edge *e_=(s_);e_;e_=e_->e)
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
IO<1000000, 1000000> io;

cint N = 200003, S = 456, mo = 1000000007;

inline int chk(cint x) {
    return x >= mo ? x - mo : x;
}
inline int chk2(cint x) {
    return x < 0 ? x + mo : x;
}
inline void add(int &x, cint v) {
    x = chk(x + v);
}
int n, sz, a[N], b[N], c[N], d[S][S];
void update(cint x, cint y, cint v) {
    if (x >= sz)
        for (int i = y; i <= n; i += x) add(a[i], v), add(c[b[i]], v);
    else {
        int *f = d[x];
        re (i, y == x ? 0: y, x) add(f[i], v);
    }
}
int query(cint l, cint r) {
    cint bl = b[l], br = b[r];
    int res = 0;
    if (bl == br)
        rep (i, l, r) add(res, a[i]);
    else {
        for (int i = l; b[i] == bl; ++i) add(res, a[i]);
        for (int i = r; b[i] == br; --i) add(res, a[i]);
        re (i, bl + 1, br) add(res, c[i]);
    }
    re (i, 1, sz) {
        cint *f = d[i];
        ll x = (r - l) / i;
        int dl = l % i, dr = r % i;
        if (dl <= dr) {
            ll y = dl ? chk2(f[dr] - f[dl - 1]) : f[dr];
            res = (y * (x + 1) + chk2(f[i - 1] - y) * x + res) % mo;
        } else {
            ++dr; --dl;
            ll y = chk2(f[dl] - f[dr - 1]);
            res = (y * x + 
                   chk2(f[i - 1] - y) * (x + 1) + res) % mo;
        }
    }
    return res;
}
int main() {
    int m;
    io >> n >> m;
    int cc = sz = n > 60 ? sqrt(n / 18) : (n >= 10 ? sqrt(n / 10) : 1);
    rep (i, 1, n) {
        io >> a[i];
        if (++cc > sz) cc = 1, b[i] = b[i - 1] + 1;
        else b[i] = b[i - 1];
        add(c[b[i]], a[i]);
    }
    while (m--) {
        char op;
        int l, r;
        io >> op >> l >> r;
        if (op == '1') update(l, r, io);
        else io << query(l, r) daze;
    }
}
