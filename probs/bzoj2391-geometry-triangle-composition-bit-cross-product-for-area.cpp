#include <bits/stdc++.h>
#define rep(i_,s_,t_) for(int i_=(s_);i_<=(t_);++i_)
#define re(i_,s_,t_) for(int i_=(s_);i_<(t_);++i_)
#define per(i_,s_,t_) for(int i_=(s_);i_>=(t_);--i_)
#define pe(i_,s_,t_) for(int i_=(s_);i_>(t_);--i_)
#define koishi(e_,u_) for(Edge *e_=(u)_->e;e_;e_=e_->e)
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
cint p_[]={10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};template<cint LI,cint LO>struct IO{char a[LI],b[LO],r[30],*s,*t,*z,c;IO():z(b){}~IO(){if(z!=b)fwrite(b,1,z-b,stdout);}char gc(){if(s==t)t=(s=a)+fread(a,1,LI,stdin);return s==t?EOF:*s++;}template<class T>IO&oper>>(T&x){for(c=gc();c!='-'&&!isdigit(c);c=gc());bool f=c=='-';if(f)c=gc();x=c-'0';for(c=gc();isdigit(c);c=gc())x=x*10+(c-'0');if(f)x=-x;return*this;}IO&oper>>(char*x){for(c=gc();!isgraph(c);c=gc());*x++=c;for(c=gc();isgraph(c);*x++=c,c=gc());*x=0;return*this;}IO&oper>>(char&x){for(x=gc();!isgraph(x);x=gc());return*this;}IO&oper>>(double&x){int p,y;*this>>p;if(c=='.'){*this>>y;for(x=y;x>1;x/=10);if(p<0)x=p-x;else x+=p;}else x=p;return*this;}template<class T>oper T(){T x;*this>>x;return x;}void pc(cchar x){if(z==b+LO)fwrite(z=b,1,LO,stdout);*z++=x;}void fl(){fwrite(b,1,z-b,stdout);z=b;}template<class T>struct d{T x;int l;d(const T x_,cint l_):x(x_),l(l_){}oper T&(){return x;}};template<class T>d<T>operator()(const T x,cint l){return d<T>(x,l);}template<class T>IO&oper<<(T x){if(x==0)pc('0');else{if(x<0)pc('-'),x=-x;T y;char*j=r;for(;x;x=y)y=x/10,*j++=x-y*10+'0';while(j!=r)pc(*--j);}return*this;}template<class T>IO&oper<<(d<T>x){if(x==0)re(i,0,x.l)pc('0');else{if(x<0)pc('-'),x.x=-x;T y;char*j=r;for(;x;x.x=y,--x.l)y=x/10,*j++=x-y*10+'0';for(;x.l;pc('0'),--x.l);while(j!=r)pc(*--j);}return*this;}IO&oper<<(d<double>x){if(std::isnan(x))return*this<<"nan";if(std::isinf(x))return*this<<"inf";if(x<0)pc('-'),x.x=-x;int w=floor(x);*this<<w;pc('.');int e=(x-w)*p_[x.l],u=e/10;if(e-u*10>=5)++u;return*this<<d<int>(u,x.l);}IO&oper<<(const double x){return*this<<d<double>(x,6);}IO&oper<<(char*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar*x){while(*x)pc(*x++);return*this;}IO&oper<<(cchar x){return pc(x),*this;}template<class T>void oper()(T x){*this<<x;}};
IO<1000000, 1000000> io;

cint N = 1002, inf = 10002;

struct Point {
    int x, y, w;
    Point() {}
    Point(cint x_, cint y_) : x(x_), y(y_), w(-inf) {}
    Point oper - (const Point &rh) const {
        return Point(x - rh.x, y - rh.y);
    }
    bool oper == (const Point &rh) const {
        return x == rh.x && y == rh.y;
    }
} a[N + N], b[N], ps[N + N], cent, ori = Point(-inf - 3, -inf -7);
int cross(const Point &p, const Point &q) {
    return p.x * q.y - p.y * q.x;
}
bool cmp(const Point &p, const Point &q) {
    return cross(p - ori, q - ori) > 0;
}
bool cmp2(const int i, const int j) {
    /* if (a[i] == cent) return true;
    if (a[j] == cent) return true;
    int ti = cross(cent - ori, a[i] - cent), tj = cross(cent - ori, a[j] - cent);
    if (ti < 0 && tj > 0) return tj;
    if (tj < 0 && ti > 0) return ti; */
    return cross(ps[i] - cent, ps[j] - cent) < 0;
}
int sgn(const int x) {
    return x ? (x > 0 ? 1 : -1) : 0;
}
int h;
namespace bit {
    int c[N + N];
    void add(int i, cint x) {
        for (; i <= h; i += i & -i)
            c[i] += x;
    }
    int query(int i) {
        int res = 0;
        for (; i; i -= i & -i)
            res += c[i];
        return res;
    }
    void clear() {
        rep (i, 1, h)
            c[i] = 0;
    }
}
int n, m, q, f[N][N];
int main() {
    io >> n >> m;
    int hh = n + m;
    rep (i, 1, n) {
        io >> a[i].x >> a[i].y;
        a[i].w = -i;
    }
    rep (i, n + 1, hh)
        io >> a[i].x >> a[i].y >> a[i].w;
    std::sort(a + 1, a + hh + 1, cmp); // *
    rep (i, 1, hh) if (a[i].w < 0)
        b[-a[i].w] = a[i];
    io >> q;
    rep (i, 1, n) {
        static int sa[N + N], rk[N + N];
        cent = b[i];
        h = 0;
        rep (j, 1, hh) if (cross(cent - ori, a[j] - ori) > 0) {
            ps[++h] = a[j];
            sa[h] = h;
        }
        std::sort(sa + 1, sa + h + 1, cmp2);
        rep (j, 1, h)
            rk[sa[j]] = j;
        crep (j, 1, h)
            ccc(j, sa[j], rk[j], ps[sa[j]].x, ps[sa[j]].y, ps[sa[j]].w, b[i].x, b[i].y);
        bit::clear();
        rep (j, 1, h) {
            const Point &p = ps[j];
            ccc(j, rk[j], ps[j].x, ps[j].y, ps[j].w);
            if (p.w < 0)
                f[i][-p.w] = bit::query(rk[j]);
            else
                bit::add(rk[j], p.w);
        }
    }
    crep (i, 1, n) crep (j, 1, n) ccc(i, j, f[i][j]);
    while (q--) {
        int k = io, ans = 0;
        int last = io;
        const int fir = last;
        re (i, 1, k) {
            int t = io;
            ans += sgn(cross(b[t] - ori, b[last] - ori)) * std::max(f[t][last], f[last][t]);
            last = t;
        }
        io << std::abs(ans + sgn(cross(b[fir] - ori, b[last] - ori)) * std::max(f[fir][last], f[last][fir])) daze;
    }

    return 0;
}
